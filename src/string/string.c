/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** string
*/

#include <stddef.h>
#include <stdlib.h>

#include "string.h"

size_t str_len(const char *str)
{
    return str_len_until(str, '\0');
}

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
    size_t str_length = str_len(str);
    if (len > str_length || len == 0) len = str_length;

    char *result = malloc(sizeof(char) * (len + 1));
    if (result == NULL) return NULL;

    for (size_t i = 0; i < len; i++) {
        result[i] = str[i];
    }
    result[len] = '\0';

    return result;
}

char *str_concat(const char *str1, const char *str2, const char* sep)
{
    if (str1 == NULL) return str_copy(str2, 0);
    if (str2 == NULL) return str_copy(str1, 0);
    if (sep == NULL) sep = "";

    size_t str1_length = str_len(str1);
    size_t str2_length = str_len(str2);
    size_t sep_length = str_len(sep);

    char *result = malloc(
        sizeof(char) * (str1_length + str2_length + sep_length + 1));
    if (result == NULL) return NULL;

    for (size_t i = 0; i < str1_length; i++)
        result[i] = str1[i];
    for (size_t i = 0; i < sep_length; i++)
        result[str1_length + i] = sep[i];
    for (size_t i = 0; i < str2_length; i++)
        result[str1_length + sep_length + i] = str2[i];
    result[str1_length + sep_length + str2_length] = '\0';
    return result;
}

int str_compare(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL) return 1;
    size_t str1_length = str_len(str1);
    size_t str2_length = str_len(str2);

    if (str1_length > str2_length) return 1;
    if (str1_length < str2_length) return -1;

    for (size_t i = 0; i < str1_length; i++) {
        if (str1[i] > str2[i]) return 1;
        if (str1[i] < str2[i]) return -1;
    }

    return 0;
}
