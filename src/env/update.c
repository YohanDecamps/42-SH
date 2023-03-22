/*
** EPITECH PROJECT, 2023
** shell
** File description:
** update
*/

#include <stdlib.h>

#include "shell/env.h"
#include "shell/util.h"
#include "shell/string.h"

char *sh_env_get(sh_env_t *env, const char *key)
{
    for (size_t i = 0; i < env->env_size; i++) {
        if (str_compare(env->env[i].key, key) == 0) {
            return env->env[i].value;
        }
    }
    return NULL;
}

void sh_env_set(sh_env_t *env, const char *key, const char *value)
{
    for (size_t i = 0; i < env->env_size; i++) {
        if (str_compare(env->env[i].key, key) == 0) {
            free(env->env[i].value);
            env->env[i].value = str_copy(value, 0);
            return;
        }
    }

    sh_env_add(env, key, value);
}

void sh_env_add(sh_env_t *env, const char *key, const char *value)
{
    if (env->env_size == env->env_capacity) {
        env->env_capacity += 5;
        size_t old_size = env->env_size * sizeof(sh_env_kv_t);
        size_t new_size = env->env_capacity * sizeof(sh_env_kv_t);
        env->env = mem_realloc(env->env, old_size, new_size);
    }

    env->env[env->env_size].key = str_copy(key, 0);
    env->env[env->env_size].value = str_copy(value, 0);
    env->env_size++;
}

void sh_env_unset(sh_env_t *env, const char *key)
{
    for (size_t i = 0; i < env->env_size; i++) {
        if (str_compare(env->env[i].key, key) == 0) {
            free(env->env[i].key);
            free(env->env[i].value);
            env->env[i] = (sh_env_kv_t) {NULL, NULL};
            return;
        }
    }
}
