/*
** EPITECH PROJECT, 2023
** shell
** File description:
** prompt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell/macros.h"
#include "shell/prompt.h"
#include "shell/command.h"

int interactive_prompt(sh_env_t *env)
{
    char *input = NULL;
    size_t input_size = 0;

    while (env->exit == false) {
        write(STDOUT, "$> ", 3);
        if (getline(&input, &input_size, stdin) == -1) {
            env->exit = true;
        } else {
            run_command(input, env);
        }
    }

    if (input != NULL)
        free(input);

    if (env->exit_silent == false)
        write(STDOUT, "exit\n", 5);
    return env->exit_status;
}

int non_interactive_command(sh_env_t *env)
{
    char *input = NULL;
    size_t input_size = 0;

    while (env->exit == false) {
        if (getline(&input, &input_size, stdin) == -1) {
            env->exit = true;
        } else {
            run_command(input, env);
        }
    }

    if (input != NULL)
        free(input);
    return env->exit_status;
}
