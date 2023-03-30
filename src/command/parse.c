/*
** EPITECH PROJECT, 2023
** shell
** File description:
** command
*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell/command.h"
#include "shell/macros.h"
#include "shell/string.h"

void print_command_error(command_res_t res)
{
    if (res == CMD_RES_EMPTY)
        write(STDERR, "Invalid null command.\n", 22);
    if (res == CMD_RES_REDIRECT_NAME)
        write(STDERR, "Missing name for redirect.\n", 27);
    if (res == CMD_RES_REDIRECT_AMBIGUOUS)
        write(STDERR, "Ambiguous input redirect.\n", 26);
    if (res == CMD_RES_NOT_IMPLEMENTED)
        write(STDERR, "Not implemented.\n", 17);
}

static bool handle_separator(token_list_t *tokens, size_t *index,
    command_group_t **group, command_exec_t *exec)
{
    if (tokens->tokens[*index].type == TOK_PIPE) {
        (*index) += 1;
        return true;
    }
    if (tokens->tokens[*index].type == TOK_SEMICOLON) {
        (*index) += 1;
        *group = command_exec_add_group(exec);
        return true;
    }

    return false;
}

command_exec_t *parse_command_exec(token_list_t *tokens)
{
    command_exec_t *exec = command_exec_new();
    if (exec == NULL) return NULL;
    command_group_t *group = command_exec_add_group(exec);
    if (group == NULL) return NULL;

    size_t index = 0;
    while (index < tokens->size) {
        if (handle_separator(tokens, &index, &group, exec))
            continue;

        command_t *command = command_group_add_command(group);
        if (command == NULL) return NULL;
        command_res_t res = command_parse(tokens, &index, command);
        if (res != CMD_RES_OK) {
            print_command_error(res);
            command_exec_free(exec);
            return NULL;
        }
    }
    return exec;
}
