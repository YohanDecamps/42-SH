/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** string
*/

#include <stddef.h>
#include <stdlib.h>

#include "string.h"

size_t str_len_until(const char *str, char delimiter)
{
    size_t len = 0;
    while (str[len] != '\0' && str[len] != delimiter) len++;

    return len;
}

char *str_copy(const char *str, size_t len)
{
    size_t str_length = str_len_until(str, '\0');
    if (len > str_length || len == 0) len = str_length;

    char *result = malloc(sizeof(char) * (len + 1));
    if (result == NULL) return NULL;

    for (size_t i = 0; i < len; i++) {
        result[i] = str[i];
    }
    result[len] = '\0';

    return result;
}

char **str_split_once(const char *str, char delimiter)
{
    char **result = malloc(sizeof(char *) * 2);
    if (result == NULL) return NULL;

    size_t str_length = str_len_until(str, '\0');
    size_t start_index = str_len_until(str, delimiter);

    result[0] = str_copy(str, start_index);
    result[1] = str_copy(str + start_index + 1, str_length - start_index - 1);

    return result;
}
