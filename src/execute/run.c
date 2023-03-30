/*
** EPITECH PROJECT, 2023
** shell
** File description:
** run
*/

#include "shell/execute.h"
#include "shell/command.h"
#include "shell/macros.h"
#include "shell/tokenizer.h"
#include "shell/resolve.h"

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
        if (run_command_group(&exec->groups[i], env) == ERROR_RETURN) {
            command_exec_free(exec);
            token_list_free(tokens);
            return ERROR_RETURN;
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
