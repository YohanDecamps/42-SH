/*
** EPITECH PROJECT, 2023
** shell
** File description:
** print
*/

#include <stdio.h>

#include "shell/macros.h"
#include "shell/prompt.h"

static void print_from_cursor(line_buffer_t *line)
{
    printf("%s%s", A_ERASE, line->buffer + line->cursor);
    for (size_t i = 0; i < line->size - line->cursor; i++)
        printf(A_MLEFT);
}

int print_char(line_buffer_t *line, char input)
{
    if (line_buffer_add(line, input) == ERROR_RETURN)
        return ERROR_RETURN;

    printf("%c", input);
    print_from_cursor(line);
    return SUCCESS_RETURN;
}

void delete_char(line_buffer_t *line)
{
    if (line->cursor > 0) {
        line_buffer_remove(line);
        printf(A_MLEFT);
        print_from_cursor(line);
    }
}

void move_cursor_left(line_buffer_t *line, size_t n)
{
    for (size_t i = 0; i < n && line->cursor > 0; i++) {
        line->cursor--;
        printf(A_MLEFT);
    }
}

void move_cursor_right(line_buffer_t *line, size_t n)
{
    for (size_t i = 0; i < n && line->cursor < line->size; i++) {
        line->cursor++;
        printf(A_MRIGHT);
    }
}
