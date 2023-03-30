/*
** EPITECH PROJECT, 2023
** shell
** File description:
** env
*/

#include <unistd.h>

#include "shell/macros.h"
#include "shell/builtin.h"
#include "shell/util.h"
#include "shell/string.h"

int builtin_env(command_t *command, sh_env_t *env)
{
    size_t args_len = command->args.size - 1;

    if (args_len > 0) {
        write(STDERR, "env: '", 6);
        write(STDERR, command->args.argv[1], str_len(command->args.argv[1]));
        write(STDERR, "': No such file or directory\n", 29);
        return 127;
    }

    for (size_t i = 0; i < env->env_size; i++) {
        sh_env_kv_t var = env->env[i];
        if (var.key == NULL) continue;
        write(command->out.fd, var.key, str_len(var.key));
        write(command->out.fd, "=", 1);
        write(command->out.fd, var.value, str_len(var.value));
        write(command->out.fd, "\n", 1);
    }

    return 0;
}

static bool is_alphanumeric(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    if (c >= 'A' && c <= 'Z')
        return true;
    if (c >= 'a' && c <= 'z')
        return true;
    return false;
}

int builtin_setenv(command_t *command, sh_env_t *env)
{
    size_t args_len = command->args.size - 1;
    if (args_len < 1)
        return builtin_env(command, env);
    if (args_len > 2) {
        write(STDERR, "setenv: Too many arguments.\n", 28);
        return 1;
    }
    size_t key_len = str_len(command->args.argv[1]);
    for (size_t i = 0; i < key_len; i++) {
        if (!is_alphanumeric(command->args.argv[1][i])) {
            write(STDERR, "setenv: Variable name must contain", 34);
            write(STDERR, " alphanumeric characters.\n", 26);
            return 1;
        }
    }

    char *key = command->args.argv[1];
    char *value = args_len == 2 ? command->args.argv[2] : "";
    sh_env_set(env, key, value);
    return 0;
}

int builtin_unsetenv(command_t *command, sh_env_t *env)
{
    size_t args_len = command->args.size - 1;
    if (args_len == 0) {
        write(STDERR, "unsetenv: Too few arguments.\n", 29);
        return 1;
    }

    for (size_t i = 1; i < args_len + 1; i++) {
        sh_env_unset(env, command->args.argv[i]);
    }
    return 0;
}
