/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** parse
*/


#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

#include "util.h"
#include "macros.h"

char **str_split(const char *str, char delimiter)
{
    if (str == NULL) return NULL;

    size_t part_count = 1;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == delimiter) part_count++;
    }

    char **result = malloc(sizeof(char *) * (part_count + 1));
    if (result == NULL) return NULL;

    size_t start_index = 0;
    for (size_t i = 0; i < part_count; i++) {
        size_t part_size = str_len_until(str + start_index, delimiter);
        result[i] = str_copy(str + start_index, part_size);
        start_index += part_size + 1;
    }

    result[part_count] = NULL;
    return result;
}

char **str_split_once(const char *str, char delimiter)
{
    if (str == NULL) return NULL;
    char **result = malloc(sizeof(char *) * 2);
    if (result == NULL) return NULL;

    size_t str_length = str_len(str);
    size_t start_index = str_len_until(str, delimiter);

    result[0] = str_copy(str, start_index);
    result[1] = str_copy(str + start_index + 1, str_length - start_index - 1);

    return result;
}

char *str_trim(char *str)
{
    if (str == NULL) return NULL;
    size_t string_length = str_len(str);
    if (string_length == 0) return str;

    size_t start_index = 0;
    size_t end_index = string_length - 1;
    while (str[start_index] == ' ' || str[start_index] == '\n') start_index++;
    while ((str[end_index] == ' ' || str[end_index] == '\n') &&
        end_index > start_index) {
        end_index--;
    }

    size_t new_length = end_index - start_index + 1;
    return str_copy(str + start_index, new_length);
}

int str_parse_int(const char *str, int *number)
{
    size_t n = 0;
    int sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') return ERROR_RETURN;
        size_t parsed = str[i] - '0';

        if (n > SIZE_MAX / 10 ||
            (n == SIZE_MAX / 10 && parsed > SIZE_MAX % 10))
            return ERROR_RETURN;
        n = n * 10 + parsed;
    }

    *number = (int) n * sign;
    return SUCCESS_RETURN;
}
