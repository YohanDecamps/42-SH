/*
** EPITECH PROJECT, 2023
** shell
** File description:
** command
*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell/command_new.h"
#include "shell/macros.h"
#include "shell/string.h"

static void print_command_error(command_res_t res)
{
    if (res == CMD_RES_EMPTY)
        write(STDERR, "Invalid null command.\n", 22);
}

command_res_t command_parse(token_list_t *tokens, size_t *index,
    command_t *command)
{
    while (*index < tokens->size) {
        token_t *token = &tokens->tokens[*index];
        if (token->type == TOK_PIPE || token->type == TOK_SEMICOLON)
            return CMD_RES_OK;

        if (token->type == TOK_WORD)
            command_push_arg(command, token->value);
    }
    return CMD_RES_OK;
}
