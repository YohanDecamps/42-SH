/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** resolver
*/

#include <stdlib.h>
#include <unistd.h>

#include "command.h"
#include "string.h"

static char *expand_home(char *path, char *home)
{
    if (*path != '~') return path;
    char *expanded = str_concat(home, path + 1);
    free(path);
    return expanded;
}

static char *resolve_directory(char *path, char *directory)
{
    char *resolve_path = str_concat(directory, path);

    if (access(resolve_path, X_OK) == 0) {
        free(path);
        return resolve_path;
    }

    free(resolve_path);
    return NULL;
}

char *resolve_path(char *path, sh_env_t *env)
{
    if (path == NULL) return NULL;
    if (*path == '/' || *path == '.') return path;

    if (*path == '~') {
        char *home = sh_env_get(env, "HOME");
        if (home == NULL) return NULL;
        return expand_home(path, home);
    }

    char **path_dirs = env->path;
    if (path_dirs == NULL) return path;

    for (size_t i = 0; path_dirs[i] != NULL; i++) {
        char *resolved = resolve_directory(path, path_dirs[i]);
        if (resolved != NULL) return resolved;
    }
    return path;
}
