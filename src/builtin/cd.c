/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** cd
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtin.h"
#include "macros.h"
#include "util.h"

static char *cd_parse_args(sh_command_t *command, sh_env_t *env)
{
    size_t args_count = mem_array_len(command->args) - 1;
    char *home = sh_env_get(env, "HOME");
    char *path = command->args[1];

    if (args_count > 1) {
        write(STDERR, "cd: Too many arguments.\n", 24);
        return NULL;
    }
    if (args_count == 0 && home == NULL) {
        write(STDERR, "cd: No home directory.\n", 23);
        return NULL;
    }
    if (args_count == 1 && *path == '~' && home == NULL) {
        write(STDERR, "No $home variable set.\n", 23);
        return NULL;
    }
    if (args_count == 0) path = home;
    if (*path == '~') path = expand_home(path, home);

    return str_copy(path, 0);
}

int builtin_cd(sh_command_t *command, sh_env_t *env)
{
    char *path = cd_parse_args(command, env);
    if (path == NULL) return 1;

    if (chdir(path) == -1) {
        perror(path);
        free(path);
        return 1;
    }

    free(path);
    return 0;
}
