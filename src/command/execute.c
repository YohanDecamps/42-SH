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

#include "builtin.h"
#include "command.h"
#include "macros.h"
#include "mem.h"

static void child_exec(sh_command_t *command, sh_env_t *env)
{
    char **envp = sh_env_to_array(env);
    if (envp == NULL) return;

    if (execve(command->path, command->args, envp) == -1)
        perror(command->path);

    mem_free_array(envp);
    env->exit_status = 1;
    env->exit_silent = true;
    env->exit = true;

    return;
}

static void wait_process(pid_t pid, sh_env_t *env)
{
    int wstatus;
    while (1) {
        if (waitpid(pid, &wstatus, 0) == -1) {
            perror("waitpid");
            return;
        }

        if (WIFEXITED(wstatus)) {
            env->exit_status = WEXITSTATUS(wstatus);
            return;
        }
        if (WIFSIGNALED(wstatus)) {
            int signal = WTERMSIG(wstatus);
            char *signal_name = strsignal(signal);
            write(STDERR, signal_name, strlen(signal_name));
            write(STDERR, "\n", 1);
            env->exit_status = 128 + signal;
            return;
        }
    }
}

void command_exec(sh_command_t *command, sh_env_t *env)
{
    if (command == NULL) return;
    if (command->path == NULL || *command->path == '\0') return;

    if (command->builtin)
        return builtin_exec(command, env);

    pid_t child_pid = fork();

    if (child_pid == 0) {
        child_exec(command, env);
    } else if (child_pid > 0) {
        wait_process(child_pid, env);
    } else {
        perror("fork");
    }
}
