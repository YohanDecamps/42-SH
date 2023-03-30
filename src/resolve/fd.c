/*
** EPITECH PROJECT, 2023
** shell
** File description:
** fd
*/

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "shell/command.h"
#include "shell/macros.h"
#include "shell/resolve.h"
#include "shell/util.h"

static int open_fd(fd_t *fd, int flags, int mode)
{
    fd->fd = open(fd->path, flags, mode);
    if (fd->fd == -1) {
        print_error(fd->path, errno, true);
        return ERROR_RETURN;
    }
    return SUCCESS_RETURN;
}

static int resolve_command_fd(command_t *command)
{
    if (command->in.type == FD_FILE) {
        if (open_fd(&command->in, READ_FLAGS, 0) == ERROR_RETURN)
            return ERROR_RETURN;
    }
    if (command->out.type == FD_FILE) {
        if (open_fd(&command->out, WRITE_FLAGS, WRITE_MODE) == ERROR_RETURN)
            return ERROR_RETURN;
    }
    if (command->out.type == FD_APPEND) {
        if (open_fd(&command->out, APPEND_FLAGS, WRITE_MODE) == ERROR_RETURN)
            return ERROR_RETURN;
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
        if (command->in.fd != FD_NULL && command->in.fd != STDIN)
            close(command->in.fd);
        if (command->in.fd != FD_NULL && command->out.fd != STDOUT)
            close(command->out.fd);
    }
}
