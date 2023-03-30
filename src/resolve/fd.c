/*
** EPITECH PROJECT, 2023
** shell
** File description:
** fd
*/

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "shell/macros.h"
#include "shell/resolve.h"
#include "shell/util.h"

static int resolve_command_fd(command_t *command)
{
    if (command->in.type == FD_FILE) {
        command->in.fd = open(command->in.path, READ_FLAGS);
        if (command->in.fd == -1) {
            print_error(command->in.path, errno, true);
            return ERROR_RETURN;
        }
    }
    if (command->out.type == FD_FILE) {
        command->out.fd = open(command->out.path, WRITE_FLAGS, WRITE_MODE);
        if (command->out.fd == -1) {
            print_error(command->out.path, errno, true);
            return ERROR_RETURN;
        }
    }
    return SUCCESS_RETURN;
}

int resolve_group_fd(command_group_t *group)
{
    for (size_t i = 0; i < group->size; i++) {
        command_t *command = &group->commands[i];
        if (resolve_command_fd(command) == ERROR_RETURN)
            return ERROR_RETURN;
    }
    return SUCCESS_RETURN;
}

void close_group_fd(command_group_t *group)
{
    for (size_t i = 0; i < group->size; i++) {
        command_t *command = &group->commands[i];
        if (command->in.fd != STDIN)
            close(command->in.fd);
        if (command->out.fd != STDOUT)
            close(command->out.fd);
    }
}
