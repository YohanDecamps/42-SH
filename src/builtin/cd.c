/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** cd
*/

#include <stdio.h>
#include <unistd.h>

#include "builtin.h"
#include "macros.h"
#include "util.h"

int builtin_cd(sh_command_t *command, sh_env_t *env)
{
    char *home = sh_env_get(env, "HOME");
    char *path = command->args[1];

    if (path == NULL && home == NULL) {
        write(STDERR, "cd: No home directory.\n", 23);
        return 0;
    }
    if (path != NULL && *path == '~' && home == NULL) {
        write(STDERR, "No $home variable set.\n", 23);
        return 0;
    }

    if (path == NULL) path = home;
    if (*path == '~') path = expand_home(path, home);

    if (chdir(path) == -1) {
        perror(path);
        return 1;
    }
    return 0;
}
