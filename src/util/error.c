/*
** EPITECH PROJECT, 2023
** shell
** File description:
** error
*/

#include <string.h>
#include <unistd.h>

#include "macros.h"
#include "util.h"

void print_error(const char *prefix, int code)
{
    if (prefix != NULL) {
        write(STDERR, prefix, str_len(prefix));
        write(STDERR, ": ", 2);
    }

    char *error = strerror(code);
    write(STDERR, error, str_len(error));
    write(STDERR, ".", 1);
}
