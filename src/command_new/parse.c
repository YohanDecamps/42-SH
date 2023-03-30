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

void print_command_error(command_res_t res)
{
    if (res == CMD_RES_EMPTY)
        write(STDERR, "Invalid null command.\n", 22);
    if (res == CMD_RES_REDIRECT_NAME)
        write(STDERR, "Missing name for redirect.\n", 27);
}

command_res_t command_parse_inner(token_list_t *tokens, size_t *index,
    command_t *command)
{
    token_t *token = &tokens->tokens[*index];
    if (token->type == TOK_PIPE || token->type == TOK_SEMICOLON)
        return CMD_RES_OK;

    if (token->type == TOK_WORD) {
        command_push_arg(command, token->value);
        *index += 1;
    }

    if (token->type == TOK_REDIRECT_IN)
        return parse_redirect_in(tokens, index, command);
    if (token->type == TOK_REDIRECT_OUT)
        return parse_redirect_out(tokens, index, command);
    if (token->type == TOK_APPEND_OUT)
        return parse_append_out(tokens, index, command);
    if (token->type == TOK_APPEND_IN)
        return parse_append_in(tokens, index, command);

    return CMD_RES_OK;
}

command_res_t command_parse(token_list_t *tokens, size_t *index,
    command_t *command)
{
    while (*index < tokens->size) {
        command_res_t res = command_parse_inner(tokens, index, command);
        if (res != CMD_RES_OK)
            return res;
    }
    return CMD_RES_OK;
}
