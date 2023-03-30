/*
** EPITECH PROJECT, 2023
** shell
** File description:
** resolve
*/

#pragma once

#include "shell/command.h"
#include "shell/env.h"

/**
 * @brief Resolve command group path, arguments and file descriptors.
 *
 * @param group Command group to resolve
 * @param env Shell environment
 * @return int 0 on success, -1 on error.
 */
int resolve_command_group(command_group_t *group, sh_env_t *env);

/**
 * @brief Resolve a path, using the PATH environment variable and expand it
 * with the $HOME environment variable.
 *
 * @param path Path to resolve
 * @param env Shell environment
 * @return char* Resolved path.
 */
char *resolve_path(char *path, sh_env_t *env);

/**
 * @brief Expand home path in arguments.
 *
 * @param args Arguments to expand
 * @param env Shell environment
 */
int expand_args_home(command_args_t *args, sh_env_t *env);
