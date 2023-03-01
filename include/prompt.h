/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** prompt
*/

#ifndef PROMPT_H_
    #define PROMPT_H_

    #include "env.h"

    /**
     * @brief Display interactive prompt.
     *
     * @param env Shell environment.
     * @return int Shell exit status.
     */
    int interactive_prompt(sh_env_t *env);

    /**
     * @brief Execute command in non-interactive mode.
     *
     * @param env Shell environment.
     * @return int Shell exit status.
     */
    int non_interactive_command(sh_env_t *env);

#endif /* !PROMPT_H_ */
