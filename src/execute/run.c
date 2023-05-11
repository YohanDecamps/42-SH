/*
** EPITECH PROJECT, 2023
** shell
** File description:
** run
*/

#include "shell/env.h"
#include "shell/execute.h"
#include "shell/command.h"
#include "shell/macros.h"
#include "shell/tokenizer.h"
#include "shell/resolve.h"
#include <stddef.h>

static int run_command_group(command_group_t *group, sh_env_t *env)
{
    if (group == NULL) return ERROR_RETURN;
    if (resolve_command_group(group, env) == ERROR_RETURN) return ERROR_RETURN;

    for (size_t i = 0; i < group->size; i++) {
        command_exec(&group->commands[i], env);
    }

    close_group_fd(group);
    return SUCCESS_RETURN;
}

static int check_run_inner(sh_env_t *env, size_t i, command_exec_t *exec,
    token_list_t *tokens)
{
    if (run_command_group(&exec->groups[i], env) == ERROR_RETURN) {
        command_exec_free(exec);
        token_list_free(tokens);
        return ERROR_RETURN;
    }

    return SUCCESS_RETURN;
}

static bool check_run_flags(sh_env_t *env, command_exec_t *exec, size_t i)
{
    size_t next_group_index = i + 1;

    if (next_group_index >= exec->size) return false;

    bool is_double_pipe =
        (exec->groups[next_group_index].flags == F_DOUBLE_PIPE);
    bool is_double_ampersand =
        (exec->groups[next_group_index].flags == F_DOUBLE_AMPERSAND);

    if (is_double_pipe && env->exit_status == 0) {
        return true;
    }

    if (is_double_ampersand && env->exit_status != 0) {
        return true;
    }

    return false;
}

static int run_inner(char *command, sh_env_t *env)
{
    token_list_t *tokens = tokenize(command);
    if (tokens == NULL) return ERROR_RETURN;
    command_exec_t *exec = parse_command_exec(tokens);
    if (exec == NULL) {
        token_list_free(tokens);
        return ERROR_RETURN;
    }

    for (size_t i = 0; i < exec->size; i++) {
        if (check_run_inner(env, i, exec, tokens) == ERROR_RETURN)
            return ERROR_RETURN;
        if (check_run_flags(env, exec, i)) {
            i++;
            continue;
        }
    }
    command_exec_free(exec);
    token_list_free(tokens);
    return SUCCESS_RETURN;
}

void command_run(char *command, sh_env_t *env)
{
    if (run_inner(command, env) == ERROR_RETURN)
        env->exit_status = 1;
}
