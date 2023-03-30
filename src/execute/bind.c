/*
** EPITECH PROJECT, 2023
** shell
** File description:
** bind
*/

#include <unistd.h>

#include "shell/command.h"
#include "shell/execute.h"
#include "shell/macros.h"

int command_bind_fd(command_t *command)
{
    if (command->in.type != FD_NULL && dup2(command->in.fd, STDIN) == -1)
        return ERROR_RETURN;
    if (command->out.type != FD_NULL && dup2(command->out.fd, STDOUT) == -1)
        return ERROR_RETURN;

    return SUCCESS_RETURN;
}
