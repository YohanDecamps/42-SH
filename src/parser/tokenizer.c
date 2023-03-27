/*
** EPITECH PROJECT, 2023
** shell
** File description:
** tokenizer
*/

#include <stdlib.h>
#include <unistd.h>

#include "shell/parser.h"
#include "shell/macros.h"

static void print_token_error(token_result_t res)
{
    if (res == TOK_RES_UNMATCHED_SIMPLE_QUOTE)
        write(STDERR, "Unmatched \"'\".\n", 15);
    if (res == TOK_RES_UNMATCHED_DOUBLE_QUOTE)
        write(STDERR, "Unmatched '\"'.\n", 15);
}

tokenizer_t *tokenize(const char *input)
{
    tokenizer_t *tokenizer = malloc(sizeof(tokenizer_t));
    if (tokenizer == NULL) return NULL;

    tokenizer->size = 0;
    tokenizer->capacity = 32;
    tokenizer->tokens = malloc(sizeof(token_t) * 32);
    if (tokenizer->tokens == NULL) return NULL;

    while (*input != '\0') {
        token_t token = {0};
        token_result_t res = next_token(&input, &token);
        if (res == TOK_RES_END) break;
        if (res != TOK_RES_OK) {
            print_token_error(res);
            tokenizer_free(tokenizer);
            return NULL;
        }
        if (tokenizer_push(tokenizer, token) == ERROR_RETURN) return NULL;
    }
    return tokenizer;
}

int tokenizer_push(tokenizer_t *tokenizer, token_t token)
{
    if (tokenizer->size == tokenizer->capacity) {
        tokenizer->capacity *= 2;
        size_t new_size = sizeof(token_t) * tokenizer->capacity;
        tokenizer->tokens = realloc(tokenizer->tokens, new_size);
        if (tokenizer->tokens == NULL) return ERROR_RETURN;
    }
    tokenizer->tokens[tokenizer->size++] = token;
    return SUCCESS_RETURN;
}

void tokenizer_free(tokenizer_t *tokenizer)
{
    free(tokenizer->tokens);
    free(tokenizer);
}
