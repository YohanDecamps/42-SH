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
    if (str == NULL) return 0;
    size_t len = 0;
    while (str[len] != '\0' && str[len] != delimiter) len++;

    return len;
}

char *str_copy(const char *str, size_t len)
{
    if (str == NULL) return NULL;
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
    if (str == NULL) return NULL;
    char **result = malloc(sizeof(char *) * 2);
    if (result == NULL) return NULL;

    size_t str_length = str_len_until(str, '\0');
    size_t start_index = str_len_until(str, delimiter);

    result[0] = str_copy(str, start_index);
    result[1] = str_copy(str + start_index + 1, str_length - start_index - 1);

    return result;
}

int str_compare(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL) return 1;
    size_t str1_length = str_len_until(str1, '\0');
    size_t str2_length = str_len_until(str2, '\0');

    if (str1_length > str2_length) return 1;
    if (str1_length < str2_length) return -1;

    for (size_t i = 0; i < str1_length; i++) {
        if (str1[i] > str2[i]) return 1;
        if (str1[i] < str2[i]) return -1;
    }

    return 0;
}
