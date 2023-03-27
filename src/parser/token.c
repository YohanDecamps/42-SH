/*
** EPITECH PROJECT, 2023
** shell
** File description:
** token
*/

#include "shell/parser.h"
#include "shell/string.h"

static token_result_t tokenize_quote(const char **input, token_t *token)
{
    size_t size = 0;
    char quote = **input;

    (*input)++;
    while ((*input)[size] != quote) {
        if ((*input)[size] == '\0' && quote == '\'')
            return TOK_RES_UNMATCHED_SIMPLE_QUOTE;
        if ((*input)[size] == '\0' && quote == '"')
            return TOK_RES_UNMATCHED_DOUBLE_QUOTE;
        size++;
    }

    token->type = TOK_WORD;
    token->value = str_copy(*input, size);

    *input += size + 1;
    return TOK_RES_OK;
}

static token_result_t tokenize_word(const char **input, token_t *token)
{
    size_t size = 0;
    while (!is_separator((*input)[size]) && (*input)[size] != '\0')
        size++;

    token->type = TOK_WORD;
    token->value = str_copy(*input, size);

    *input += size;
    return TOK_RES_OK;
}

token_result_t next_token(const char **input, token_t *token)
{
    while (is_separator(**input)) (*input)++;
    if (**input == '\0') return TOK_RES_END;

    if (**input == '\'' || **input == '"')
        return tokenize_quote(input, token);

    return tokenize_word(input, token);
}

bool is_separator(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}
