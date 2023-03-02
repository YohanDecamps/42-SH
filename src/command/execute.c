/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** execute
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#include "builtin.h"
#include "command.h"
#include "macros.h"
#include "util.h"

static void child_exec(sh_command_t *command, sh_env_t *env)
{
    char **envp = sh_env_to_array(env);
    if (envp == NULL) return;
    if (execve(command->path, command->args, envp) == -1) {
        env->exit_status = 1;
        if (errno == ENOENT) {
            write(STDERR, command->path, str_len(command->path));
            write(STDERR, ": Command not found.", 20);
        } else {
            print_error(command->path, errno);
        }
        if (errno == ENOEXEC) {
            write(STDERR, " Wrong architecture.", 20);
            env->exit_status = 126;
        }
        write(STDERR, "\n", 1);
    }
    mem_free_array(envp);
    env->exit_status = 1;
    env->exit_silent = true;
    env->exit = true;
}

static void signal_error(int wstatus, sh_env_t *env)
{
    int signal = WTERMSIG(wstatus);
    if (signal == SIGFPE) {
        write(STDERR, "Floating exception", 18);
    } else {
        char *signal_name = strsignal(signal);
        write(STDERR, signal_name, str_len(signal_name));
    }

    if (WCOREDUMP(wstatus))
        write(STDERR, " (core dumped)", 14);

    write(STDERR, "\n", 1);
    env->exit_status = 128 + signal;
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
            signal_error(wstatus, env);
            return;
        }
    }
}

void command_exec(sh_command_t *command, sh_env_t *env)
{
    if (command == NULL) return;
    if (command->path == NULL || *command->path == '\0') return;

    if (command->builtin) {
        builtin_exec(command, env);
        return;
    }

    pid_t child_pid = fork();

    if (child_pid == 0) {
        child_exec(command, env);
    } else if (child_pid > 0) {
        wait_process(child_pid, env);
    } else {
        perror("fork");
    }
}

void run_command(char *command, sh_env_t *env)
{
    sh_command_t *parsed_command = parse_command(command, env);
    if (parsed_command == NULL) {
        env->exit_status = 1;
        return;
    }

    command_exec(parsed_command, env);
    command_free(parsed_command);
}
