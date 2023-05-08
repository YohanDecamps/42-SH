/*
** EPITECH PROJECT, 2023
** shell
** File description:
** prompt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell/execute.h"
#include "shell/util.h"

int print_custom_prompt (sh_env_t *env)
{
    char *path = getcwd(NULL, 0);

    fprintf(stdout, BLUE "%s " RESET, path);
    if (env->exit_status == 0)
        fprintf(stdout, GREEN "[%d] " RESET, env->exit_status);
    else
        fprintf(stdout, RED "[%d] " RESET, env->exit_status);
    fprintf(stdout, BLUE "$> " RESET);

    free(path);

    return 0;
}

int interactive_prompt(sh_env_t *env)
{
    char *input = NULL;
    size_t input_size = 0;

    while (env->exit == false) {
        print_custom_prompt(env);

        if (getline(&input, &input_size, stdin) == -1) {
            env->exit = true;
        } else {
            command_run(input, env);
        }
    }

    if (input != NULL)
        free(input);

    if (env->exit_silent == false)
        fprintf(stdout, "exit\n");
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
            command_run(input, env);
        }
    }

    if (input != NULL)
        free(input);
    return env->exit_status;
}
