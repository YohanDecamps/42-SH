/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** env
*/

#include <stdbool.h>
#include <stddef.h>

#ifndef ENV_H_
    #define ENV_H_

    /**
     * @brief Shell environment key-value pair. If the key is NULL, the
     * structure is considered empty.
     */
    typedef struct {
        char *key;
        char *value;
    } sh_env_kv_t;

    /**
     * @brief Shell environement. Includes exit state and environment
     * variables.
     */
    typedef struct {
        bool exit;
        int exit_status;
        sh_env_kv_t *env;
        size_t env_size;
        size_t env_capacity;
        char **path;
    } sh_env_t;

    /**
     * @brief Initializes the shell environment.
     *
     * @param envp Environment variables.
     * @return sh_env_t* The initialized shell environment.
     */
    sh_env_t *sh_env_init(char **envp);

    /**
     * @brief Free the shell environment.
     *
     * @param env The shell environment.
     */
    void sh_env_free(sh_env_t *env);

    /**
     * @brief Get the value of an environment variable.
     *
     * @param env The shell environment.
     * @param key The key of the environment variable.
     * @return char* The value of the environment variable (NULL if not found).
     */
    char *sh_env_get(sh_env_t *env, const char *key);

    /**
     * @brief Set the value of an environment variable. This function will
     * reallocate the environment variables array if needed.
     *
     * @param env The shell environment.
     * @param key The key of the environment variable.
     * @param value The value of the environment variable.
     */
    void sh_env_set(sh_env_t *env, const char *key, const char *value);

    /**
     * @brief Adds a variable to the environment. This does not check if the
     * variable already exists, use `sh_env_set` instead.
     *
     * @param env The shell environment.
     * @param key The key of the environment variable.
     * @param value The value of the environment variable.
     */
    void sh_env_add(sh_env_t *env, const char *key, const char *value);

    /**
     * @brief Unset an environment variable. This will not shrink the
     * environment variables array.
     *
     * @param env The shell environment.
     * @param key The key of the environment variable.
     */
    void sh_env_unset(sh_env_t *env, const char *key);

#endif /* !ENV_H_ */
