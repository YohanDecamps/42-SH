/*
** EPITECH PROJECT, 2023
** shell
** File description:
** prompt
*/

#pragma once

#include "shell/env.h"

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
