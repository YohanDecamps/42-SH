/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** builtin
*/

#ifndef BUILTIN_H_
    #define BUILTIN_H_

    #include <stdbool.h>

    #include "command.h"
    #include "env.h"

    /**
     * @brief Check if a command is a builtin.
     *
     * @param path Command path.
     * @return bool True if builtin, false otherwise.
     */
    bool is_builtin(char *path);

    /**
     * @brief Execute builtin command.
     *
     * @param command Parsed shell command.
     * @param env Shell environment.
     */
    void builtin_exec(sh_command_t *command, sh_env_t *env);

    /**
     * @brief Execute cd builtin command.
     *
     * @param command Parsed shell command.
     * @param env Shell environment.
     * @return int Exit status.
     */
    int builtin_cd(sh_command_t *command, sh_env_t *env);

#endif /* !BUILTIN_H_ */