/*
** EPITECH PROJECT, 2023
** shell
** File description:
** exit
*/

#include <unistd.h>

#include "shell/builtin.h"
#include "shell/macros.h"
#include "shell/string.h"
#include "shell/util.h"

int builtin_exit(command_t *command, sh_env_t *env)
{
    int status = 0;
    size_t command_size = command->args.size;

    if (command_size > 2) {
        write(STDERR, "exit: Expression Syntax.\n", 25);
        return 1;
    }
    if (command_size == 2) {
        if (str_parse_int(command->args.argv[1], &status)) {
            write(STDERR, "exit: Expression Syntax.\n", 25);
            return 1;
        }
    }

    env->exit = true;
    return (int) status;
}
