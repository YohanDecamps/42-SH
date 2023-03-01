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

int builtin_setenv(sh_command_t *command, sh_env_t *env)
{
    size_t args_len = mem_array_len(command->args) - 1;
    if (args_len < 1)
        return builtin_env(command, env);
    if (args_len > 2) {
        write(STDERR, "setenv: Too many arguments.\n", 28);
        return 1;
    }

    char *key = command->args[1];
    char *value = args_len == 2 ? command->args[2] : "";

    sh_env_set(env, key, value);
    return 0;
}

int builtin_unsetenv(sh_command_t *command, sh_env_t *env)
{
    size_t args_len = mem_array_len(command->args) - 1;
    if (args_len == 0) {
        write(STDERR, "unsetenv: Too few arguments.\n", 29);
        return 1;
    }

    for (size_t i = 1; i < args_len + 1; i++) {
        sh_env_unset(env, command->args[i]);
    }
    return 0;
}
