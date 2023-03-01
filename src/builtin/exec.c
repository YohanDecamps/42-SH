/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** exec
*/

#include <unistd.h>

#include "builtin.h"
#include "macros.h"
#include "util.h"

const size_t BUILTIN_COUNT = 5;
const char *BUILTIN_LIST[5] = {"cd", "setenv", "unsetenv", "env", "exit"};

bool is_builtin(char *path)
{
    for (size_t i = 0; i < BUILTIN_COUNT; i++) {
        if (str_compare(path, BUILTIN_LIST[i]) == 0)
            return true;
    }
    return false;
}

void builtin_exec(sh_command_t *command, sh_env_t *env)
{
    int status = 0;

    if (str_compare(command->path, "cd") == 0)
        status = builtin_cd(command, env);
    if (str_compare(command->path, "env") == 0)
        status = builtin_env(command, env);
    if (str_compare(command->path, "setenv") == 0)
        status = builtin_setenv(command, env);
    if (str_compare(command->path, "exit") == 0)
        status = builtin_exit(command, env);

    env->exit_status = status;
}
