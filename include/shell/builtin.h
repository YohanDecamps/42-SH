/*
** EPITECH PROJECT, 2023
** shell
** File description:
** builtin
*/

#pragma once

#include <stdbool.h>

#include "shell/command.h"
#include "shell/env.h"

/**
 * @brief Builtin command structure.
 */
typedef struct {
    char *name;
    int (*exec)(command_t *, sh_env_t *);
} sh_builtin_t;

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
void builtin_exec(command_t *command, sh_env_t *env);

/**
 * @brief Execute cd builtin command.
 *
 * @param command Parsed shell command.
 * @param env Shell environment.
 * @return int Exit status.
 */
int builtin_cd(command_t *command, sh_env_t *env);

/**
 * @brief Execute exit builtin command.
 *
 * @param command Parsed shell command.
 * @param env Shell environment.
 * @return int Exit status.
 */
int builtin_exit(command_t *command, sh_env_t *env);

/**
 * @brief Execute alias builtin command.
 *
 * @param command Parsed shell command.
 * @param env Shell environment.
 * @return int Exit status.
 */
int builtin_alias (command_t *command, sh_env_t *env);

/**
 * @brief Execute env builtin command.
 *
 * @param command Parsed shell command.
 * @param env Shell environment.
 * @return int Exit status.
 */
int builtin_env(command_t *command, sh_env_t *env);

/**
 * @brief Execute setenv builtin command.
 *
 * @param command Parsed shell command.
 * @param env Shell environment.
 * @return int Exit status.
 */
int builtin_setenv(command_t *command, sh_env_t *env);

/**
 * @brief Execute unsetenv builtin command.
 *
 * @param command Parsed shell command.
 * @param env Shell environment.
 * @return int Exit status.
 */
int builtin_unsetenv(command_t *command, sh_env_t *env);

/**
 * @brief Execute history builtin command.
 *
 * @param command Parsed shell command.
 * @param env Shell environment.
 * @return int Exit status.
 */
int builtin_history(command_t *command, sh_env_t *env);
