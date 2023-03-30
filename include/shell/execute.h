/*
** EPITECH PROJECT, 2023
** shell
** File description:
** execute
*/

#pragma once

#include "shell/env.h"
#include "shell/command.h"

/**
 * @brief Execute a command.
 *
 * @param command The command to execute.
 * @param env The environment.
 */
void command_run(char *command, sh_env_t *env);

/**
 * @brief Execute a parsed command.
 *
 * @param command Parsed command to execute
 * @param env Shell environment
 */
void command_exec(command_t *command, sh_env_t *env);
