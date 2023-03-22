/*
** EPITECH PROJECT, 2023
** shell
** File description:
** exec
*/

#include <stddef.h>
#include <unistd.h>

#include "shell/builtin.h"
#include "shell/macros.h"
#include "shell/string.h"

const size_t BUILTIN_COUNT = 5;
const sh_builtin_t BUILTIN_COMMANDS[] = {
    {"cd", builtin_cd},
    {"env", builtin_env},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {"exit", builtin_exit},
};

bool is_builtin(char *path)
{
    for (size_t i = 0; i < BUILTIN_COUNT; i++) {
        if (str_compare(path, BUILTIN_COMMANDS[i].name) == 0)
            return true;
    }
    return false;
}

void builtin_exec(sh_command_t *command, sh_env_t *env)
{
    int status = 0;

    for (size_t i = 0; i < BUILTIN_COUNT; i++) {
        if (str_compare(command->path, BUILTIN_COMMANDS[i].name) == 0)
            status = BUILTIN_COMMANDS[i].exec(command, env);
    }

    env->exit_status = status;
}
