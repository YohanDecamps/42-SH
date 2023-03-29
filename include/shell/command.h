/*
** EPITECH PROJECT, 2023
** shell
** File description:
** command
*/

#pragma once

#include "shell/env.h"

/**
 * @brief Parsed command structure
 */
typedef struct {
    char *path;
    char **args;
    bool builtin;
} sh_command_t;

/* File descriptor */

typedef enum {
    FD_INT,
    FD_FILE,
    FD_PIPE,
} fd_type_t;

typedef struct {
    int fd;
} fn_int_t;

typedef struct {
    char *path;
} fn_file_t;

typedef union {
    fd_type_t type;
    fn_int_t int_fd;
    fn_file_t file_fd;
} fd_t;

/* Command */

typedef enum {
    COMMAND_SIMPLE,
    COMMAND_PIPE,
    COMMAND_LIST,
} command_type_t;

typedef struct {
    char *path; // Path to the executable
    char **argv; // Arguments (argv[0] is the executable name, NULL terminated)
    bool builtin;
    fd_t in;
    fd_t out;
} command_t;

typedef struct {
    command_t *commands;
    size_t size;
    size_t capacity;
} command_list_t;

typedef union {
    command_type_t type;
    command_t simple;
    command_list_t pipe;
    command_list_t list;
} command_exec_t;

/**
 * @brief Run a command (parse and execute).
 *
 * @param command Command to run
 * @param env Shell environment
 */
void run_command(char *command, sh_env_t *env);

/**
 * @brief Parse a command
 *
 * @param command Command to parse
 * @param env Shell environment
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
 * @brief Resolve a path, using the PATH environment variable and expand it
 * with the $HOME environment variable.
 *
 * @param path Path to resolve
 * @param env Shell environment
 * @return char* Resolved path.
 */
char *resolve_path(char *path, sh_env_t *env);
