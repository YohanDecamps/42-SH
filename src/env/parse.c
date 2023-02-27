/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** env
*/

#include <stdlib.h>

#include "env.h"
#include "string.h"

static size_t envp_size(char **envp)
{
    size_t size = 0;
    while (envp[size] != NULL) size++;

    return size;
}

static sh_env_kv_t *envp_parse(char **envp, size_t size)
{
    sh_env_kv_t *env = malloc(sizeof(sh_env_kv_t) * size);
    if (env == NULL) return NULL;

    for (size_t i = 0; i < size; i++) {
        char **kv = str_split_once(envp[i], '=');
        if (kv == NULL) return NULL;

        env[i] = (sh_env_kv_t) {kv[0], kv[1]};
        free(kv);
    }

    return env;
}

sh_env_t *sh_env_init(char **envp)
{
    sh_env_t *env = malloc(sizeof(sh_env_t));
    if (env == NULL) return NULL;
    size_t size = envp_size(envp);
    sh_env_kv_t *kv = envp_parse(envp, size);

    env->exit = false;
    env->exit_status = 0;
    env->env = kv;
    env->env_size = size;
    env->env_capacity = size;
    env->path = NULL;

    char *path = sh_env_get(env, "PATH");
    if (path != NULL) {
        char **parsed_path = str_split(path, ':');
        if (parsed_path == NULL) return NULL;
        env->path = parsed_path;
    }
    return env;
}

void sh_env_free(sh_env_t *env)
{
    for (size_t i = 0; i < env->env_size; i++) {
        free(env->env[i].key);
        free(env->env[i].value);
    }
    free(env->env);
    for (size_t i = 0; env->path[i] != NULL; i++) {
        free(env->path[i]);
    }
    free(env->path);
    free(env);
}