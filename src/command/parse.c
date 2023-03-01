/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** parse
*/

#include <stddef.h>
#include <stdlib.h>

#include "builtin.h"
#include "command.h"
#include "util.h"

sh_command_t *parse_command(char *command, sh_env_t *env)
{
    char *trimmed = str_trim(command);
    char **args = str_split(trimmed, ' ');
    free(trimmed);
    if (args == NULL) return NULL;

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
