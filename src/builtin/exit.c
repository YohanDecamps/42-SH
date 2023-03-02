/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** exit
*/

#include "builtin.h"
#include "macros.h"
#include "util.h"
#include <unistd.h>

int builtin_exit(sh_command_t *command, sh_env_t *env)
{
    int status = 0;
    size_t command_size = mem_array_len(command->args);

    if (command_size > 2) {
        write(STDERR, "exit: Expression Syntax.\n", 25);
        return 1;
    }
    if (command_size == 2) {
        if (str_parse_int(command->args[1], &status)) {
            write(STDERR, "exit: Expression Syntax.\n", 25);
            return 1;
        }
    }

    env->exit = true;
    return (int) status;
}
