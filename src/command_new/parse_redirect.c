/*
** EPITECH PROJECT, 2023
** shell
** File description:
** parse_redirect
*/

#include "shell/command_new.h"

command_res_t parse_redirect_in(token_list_t *tokens, size_t *index,
    command_t *command)
{
    if (*index + 1 >= tokens->size)
        return CMD_RES_REDIRECT_NAME;

    token_t *token = &tokens->tokens[*index + 1];
    if (token->type != TOK_WORD)
        return CMD_RES_REDIRECT_NAME;
    if (command->in.type != FD_NULL)
        return CMD_RES_REDIRECT_AMBIGUOUS;

    command->in = (fd_t) {FD_FILE, 0, token->value};
    *index += 2;
    return CMD_RES_OK;
}

command_res_t parse_redirect_out(token_list_t *tokens, size_t *index,
    command_t *command)
{
    if (*index + 1 >= tokens->size)
        return CMD_RES_REDIRECT_NAME;

    token_t *token = &tokens->tokens[*index + 1];
    if (token->type != TOK_WORD)
        return CMD_RES_REDIRECT_NAME;
    if (command->out.type != FD_NULL)
        return CMD_RES_REDIRECT_AMBIGUOUS;

    command->out = (fd_t) {FD_FILE, 1, token->value};
    *index += 2;
    return CMD_RES_OK;
}

command_res_t parse_append_out(token_list_t *tokens, size_t *index,
    command_t *command)
{
    (void) tokens;
    (void) index;
    (void) command;

    return CMD_RES_NOT_IMPLEMENTED;
}

command_res_t parse_append_in(token_list_t *tokens, size_t *index,
    command_t *command)
{
    (void) tokens;
    (void) index;
    (void) command;

    return CMD_RES_NOT_IMPLEMENTED;
}
