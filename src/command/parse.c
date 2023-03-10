/*
** EPITECH PROJECT, 2023
** shell
** File description:
** parse
*/

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "macros.h"
#include "builtin.h"
#include "command.h"
#include "util.h"

static int expand_single_home(char **arg, sh_env_t *env)
{
    if (**arg != '~') return SUCCESS_RETURN;

    char *home = sh_env_get(env, "HOME");
    if (home == NULL) {
        write(STDERR, "No $home variable set.\n", 23);
        return ERROR_RETURN;
    }

    char *expanded = expand_home(*arg, home);
    free(*arg);
    *arg = expanded;
    return SUCCESS_RETURN;
}

static int expand_args_home(char **args, sh_env_t *env)
{
    for (size_t i = 0; args[i] != NULL; i++) {
        if (expand_single_home(&args[i], env) == ERROR_RETURN) {
            mem_free_array(args);
            return ERROR_RETURN;
        }
    }

    return SUCCESS_RETURN;
}

sh_command_t *parse_command(char *command, sh_env_t *env)
{
    str_remove_newline(command);
    char *trimmed = str_trim(command);
    char **args = str_split(trimmed, " \t");
    free(trimmed);

    if (args == NULL) return NULL;
    if (expand_args_home(args, env) == ERROR_RETURN) return NULL;

    sh_command_t *cmd = malloc(sizeof(sh_command_t));
    if (cmd == NULL) return NULL;
    if (is_builtin(args[0])) {
        char *path = str_copy(args[0], 0);
        *cmd = (sh_command_t) {path, args, true};
    } else {
        char *path = resolve_path(args[0], env);
        *cmd = (sh_command_t) {path, args, false};
    }
    return cmd;
}

void command_free(sh_command_t *command)
{
    if (command == NULL) return;
    free(command->path);
    mem_free_array(command->args);
    free(command);
}
