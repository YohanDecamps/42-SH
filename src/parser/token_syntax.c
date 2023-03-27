/*
** EPITECH PROJECT, 2023
** shell
** File description:
** token_syntax
*/

#include "shell/parser.h"
#include "shell/string.h"

token_result_t tokenize_redirection(const char **input, token_t *token)
{
    if (**input == '<' && (*input)[1] == '<') {
        *token = (token_t) {TOK_APPEND_IN, str_copy("<<", 2)};
        *input += 2;
    }
    if (**input == '>' && (*input)[1] == '>') {
        *token = (token_t) {TOK_APPEND_OUT, str_copy(">>", 2)};
        *input += 2;
    }
    if (**input == '<' && (*input)[1] != '<') {
        *token = (token_t) {TOK_REDIRECT_IN, str_copy("<", 1)};
        *input += 1;
    }
    if (**input == '>' && (*input)[1] != '>') {
        *token = (token_t) {TOK_REDIRECT_OUT, str_copy(">", 1)};
        *input += 1;
    }
    return TOK_RES_OK;
}

token_result_t tokenize_pipe_semicolon(const char **input, token_t *token)
{
    if (**input == '|') {
        token->type = TOK_PIPE;
        token->value = str_copy("|", 1);
        *input += 1;
    }
    if (**input == ';') {
        token->type = TOK_SEMICOLON;
        token->value = str_copy(";", 1);
        *input += 1;
    }

    return TOK_RES_OK;
}
