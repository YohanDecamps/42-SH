/*
** EPITECH PROJECT, 2023
** shell
** File description:
** tokenizer
*/

#include <criterion/criterion.h>

#include "shell/parser.h"

Test(tokenizer, basic_text) {
    char *input = "ls -l";
    token_list_t *tokens = tokenize(input);

    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->size, 2);

    cr_assert_eq(tokens->tokens[0].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[0].value, "ls");

    cr_assert_eq(tokens->tokens[1].type, TOK_WORD);
    cr_assert_str_eq(tokens->tokens[1].value, "-l");
}
