/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** parse
*/

#include <stddef.h>
#include <stdlib.h>

#include "command.h"
#include "mem.h"
#include "string.h"

sh_command_t *sh_parse_command(char *command, sh_env_t *env)
{
    char *trimmed = str_trim(command);
    char **parts = str_split(trimmed, ' ');
    free(trimmed);
    if (parts == NULL) return NULL;

    sh_command_t *cmd = malloc(sizeof(sh_command_t));
    if (cmd == NULL) return NULL;

    char *path = resolve_path(parts[0], env);
    *cmd = (sh_command_t) {path, &parts[1], parts};
    return cmd;
}

void sh_command_free(sh_command_t *command)
{
    if (command == NULL) return;
    free(command->path);
    mem_free_array(command->parts);
    free(command);
}
