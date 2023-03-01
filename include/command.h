/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #include "env.h"

    /**
     * @brief Parsed command structure
     */
    typedef struct {
        char *path;
        char **args;
        bool builtin;
    } sh_command_t;

    /**
     * @brief Parse a command
     *
     * @param command Command to parse
     * @return sh_command_t* Parsed command (NULL if error)
     */
    sh_command_t *parse_command(char *command, sh_env_t *env);

    /**
     * @brief Free a parsed command
     *
     * @param command Parsed command to free
     */
    void command_free(sh_command_t *command);

    /**
     * @brief Execute a parsed command.
     *
     * @param command Parsed command to execute
     * @param env Shell environment
     */
    void command_exec(sh_command_t *command, sh_env_t *env);

    /**
     * @brief Resolve a path, using the PATH environment variable and expand
     * it with the $HOME environment variable.
     *
     * @param path Path to resolve
     * @param env Shell environment
     * @return char* Resolved path.
     */
    char *resolve_path(char *path, sh_env_t *env);

#endif /* !COMMAND_H_ */
