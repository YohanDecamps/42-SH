/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** main
*/

#include <unistd.h>
#include <stdio.h>

#include "macros.h"
#include "env.h"

int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;

    sh_env_t *env = sh_env_init(envp);
    char *input = NULL;
    size_t size = 0;

    while (1) {
        write(1, "$> ", 3);
        if (getline(&input, &size, stdin) == -1) {
            write(1, "exit\n", 5);
            sh_env_free(env);
            return SUCCESS_EXIT;
        } else {
            write(1, input, 5);
        }
    }

    sh_env_free(env);
    return SUCCESS_EXIT;
}
