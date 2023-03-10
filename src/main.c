/*
** EPITECH PROJECT, 2023
** shell
** File description:
** main
*/

#include <unistd.h>

#include "macros.h"
#include "prompt.h"
#include "env.h"

int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;

    sh_env_t *env = sh_env_init(envp);
    int exit_status = SUCCESS_EXIT;

    if (isatty(STDIN)) {
        exit_status = interactive_prompt(env);
    } else {
        exit_status = non_interactive_command(env);
    }

    sh_env_free(env);
    return exit_status;
}
