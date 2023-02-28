/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** execute
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "command.h"
#include "macros.h"

static void child_exec(sh_command_t *command, sh_env_t *env)
{
    char **envp = sh_env_to_array(env);
    if (envp == NULL) return;

    if (execve(command->path, command->args, envp) == -1)
        perror(command->path);
}

void wait_process(pid_t pid)
{
    int wstatus;

    while (1) {
        if (waitpid(pid, &wstatus, 0) == -1) {
            perror("waitpid");
            return;
        }

        if (WIFEXITED(wstatus)) {
            printf("Status: %d\n", WEXITSTATUS(wstatus));
            return;
        } else if (WIFSIGNALED(wstatus)) {
            printf("Status: %s\n", strsignal(WTERMSIG(wstatus)));
            return;
        } else if (WIFSTOPPED(wstatus)) {
            printf("Stopped by signal %d\n", WSTOPSIG(wstatus));
        } else if (WIFCONTINUED(wstatus)) {
            printf("Continued\n");
        }
    }
}

void command_exec(sh_command_t *command, sh_env_t *env)
{
    pid_t child_pid = fork();

    if (child_pid == 0) {
        child_exec(command, env);
    } else if (child_pid > 0) {
        wait_process(child_pid);
    } else {
        perror("fork");
    }
}
