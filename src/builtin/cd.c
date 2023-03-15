/*
** EPITECH PROJECT, 2023
** shell
** File description:
** cd
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "shell/builtin.h"
#include "shell/macros.h"
#include "shell/util.h"

static int cd_home(char **path, sh_env_t *env)
{
    char *home = sh_env_get(env, "HOME");
    if (home == NULL) {
        write(STDERR, "cd: No home directory.\n", 23);
        return ERROR_RETURN;
    }

    *path = home;
    return SUCCESS_RETURN;
}

static int cd_oldpwd(char **path, sh_env_t *env)
{
    char *oldpwd = sh_env_get(env, "OLDPWD");
    if (oldpwd == NULL) {
        write(STDERR, ": No such file or directory.\n", 29);
        return ERROR_RETURN;
    }

    *path = oldpwd;
    return SUCCESS_RETURN;
}

static char *cd_parse_args(sh_command_t *command, sh_env_t *env)
{
    size_t args_count = mem_array_len(command->args) - 1;
    char *path = command->args[1];

    if (args_count > 1) {
        write(STDERR, "cd: Too many arguments.\n", 24);
        return NULL;
    }

    if (args_count == 0) {
        if (cd_home(&path, env) == ERROR_RETURN)
            return NULL;
    }
    if (str_compare(path, "-") == 0) {
        if (cd_oldpwd(&path, env) == ERROR_RETURN)
            return NULL;
    }

    return str_copy(path, 0);
}

int builtin_cd(sh_command_t *command, sh_env_t *env)
{
    char *path = cd_parse_args(command, env);
    if (path == NULL) return 1;
    char *oldpwd = getcwd(NULL, 0);

    if (chdir(path) == -1) {
        print_error(path, errno);
        write(STDERR, "\n", 1);
        if (oldpwd != NULL) free(oldpwd);
        free(path);
        return 1;
    }

    if (oldpwd != NULL) {
        sh_env_set(env, "OLDPWD", oldpwd);
        free(oldpwd);
    }

    sh_env_set(env, "PWD", path);
    free(path);
    return 0;
}
