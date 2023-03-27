/*
** EPITECH PROJECT, 2023
** shell
** File description:
** parser
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>

/* Tokenizer */

typedef enum {
    TOK_WORD,
    TOK_PIPE,
    TOK_SEMICOLON,
    TOK_REDIRECT,
} token_type_t;

typedef struct {
    token_type_t type;
    char *value;
} token_t;

typedef struct {
    token_t *tokens;
    size_t size;
    size_t capacity;
} tokenizer_t;

/**
 * @brief Tokenize the given input string and return the tokens. If an error
 * occurs, NULL is returned and the error is printed to stderr.
 *
 * @param input String to tokenize.
 * @return tokenizer_t* Tokens.
 */
tokenizer_t *tokenize(const char *input);

/**
 * @brief Push a token into the tokenizer output.
 *
 * @param tokenizer The tokenizer to push the token into.
 * @param token The token to push.
 * @return int 0 on success, -1 on error.
 */
int tokenizer_push(tokenizer_t *tokenizer, token_t token);

/**
 * @brief Free the tokenizer.
 *
 * @param tokenizer The tokenizer to free.
 */
void tokenizer_free(tokenizer_t *tokenizer);

typedef enum {
    TOK_RES_OK, // Success
    TOK_RES_END, // Reached end of input
    TOK_RES_UNMATCHED_SIMPLE_QUOTE, // Error: unmatched ' quote
    TOK_RES_UNMATCHED_DOUBLE_QUOTE, // Error: unmatched " quote
} token_result_t;

/**
 * @brief Get the next token from the input string and advance the pointer
 * accordingly.
 *
 * @param input Pointer to the input string.
 * @param token Pointer to the token to fill.
 * @return token_result_t Result of the operation.
 */
token_result_t next_token(const char **input, token_t *token);

/**
 * @brief Check whether the given character is a separator (newline, space,
 * tab)
 *
 * @param c The character to check.
 * @return bool True if the character is a separator, false otherwise.
 */
bool is_separator(char c);
