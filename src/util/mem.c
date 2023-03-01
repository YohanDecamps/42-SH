/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** mem
*/

#include <stddef.h>
#include <stdlib.h>

#include "util.h"

void *mem_realloc(void *ptr, size_t size, size_t new_size)
{
    if (new_size < size)
        return ptr;

    char *new_ptr = malloc(new_size);
    if (new_ptr == NULL) return NULL;

    for (size_t i = 0; i < size; i++) {
        char byte = ((char *) ptr)[i];
        ((char *) new_ptr)[i] = byte;
    }

    free(ptr);
    return new_ptr;
}

size_t mem_array_len(char **array)
{
    size_t len = 0;
    for (size_t i = 0; array[i] != NULL; i++)
        len++;

    return len;
}

void mem_free_array(char **array)
{
    for (size_t i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
