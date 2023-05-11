/*
** EPITECH PROJECT, 2023
** shell
** File description:
** line
*/

#include <stdio.h>

#include "shell/macros.h"
#include "shell/prompt.h"
#include "shell/util.h"

static void handle_ansi_escape(line_buffer_t *line)
{
    if (getc(stdin) != '[') return;
    int code = getc(stdin);

    if (code == K_LEFT) move_cursor_left(line, 1);
    if (code == K_RIGHT) move_cursor_right(line, 1);
    if (code == K_START) move_cursor_left(line, line->cursor);
    if (code == K_END) move_cursor_right(line, line->size - line->cursor);

    if (code == K_SUPPR[0] && getc(stdin) == K_SUPPR[1]) {
        move_cursor_right(line, 1);
        delete_char(line);
    }
}

int interactive_prompt_line(line_buffer_t *line)
{
    line_buffer_reset(line);
    while (true) {
        int input = getc(stdin);

        if (input == K_EOT) return ERROR_RETURN;
        if (input == '\n') break;
        if (input == ANSI_ESC) {
            handle_ansi_escape(line);
            continue;
        }
        if (input == A_DEL) {
            delete_char(line);
            continue;
        }
        if (print_char(line, (char) input) == ERROR_RETURN)
            return ERROR_RETURN;
    }
    return SUCCESS_RETURN;
}
