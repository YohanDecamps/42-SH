/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** env
*/

#include <unistd.h>

#include "macros.h"
#include "builtin.h"
#include "util.h"

int builtin_env(sh_command_t *command, sh_env_t *env)
{
    (void) command;
    for (size_t i = 0; i < env->env_size; i++) {
        sh_env_kv_t var = env->env[i];
        if (var.key == NULL) continue;
        write(STDOUT, var.key, str_len(var.key));
        write(STDOUT, "=", 1);
        write(STDOUT, var.value, str_len(var.value));
        write(STDOUT, "\n", 1);
    }

    return 0;
}
