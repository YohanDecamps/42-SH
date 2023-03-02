/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** prompt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "macros.h"
#include "prompt.h"
#include "command.h"

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

    if (getline(&input, &input_size, stdin) == -1) {
        return SUCCESS_EXIT;
    }

    run_command(input, env);

    free(input);
    return env->exit_status;
}
