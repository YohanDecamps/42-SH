/*
** EPITECH PROJECT, 2023
** shell
** File description:
** data
*/

#include <stdlib.h>

#include "shell/command.h"
#include "shell/util.h"
#include "shell/macros.h"

command_exec_t *command_exec_new(void)
{
    command_exec_t *exec = malloc(sizeof(command_exec_t));
    if (exec == NULL) return NULL;

    exec->capacity = DEFAULT_EXEC_CAP;
    exec->size = 0;
    exec->groups = malloc(sizeof(command_group_t) * exec->capacity);

    return exec;
}

command_group_t *command_exec_add_group(command_exec_t *exec)
{
    if (exec->size == exec->capacity) {
        exec->capacity *= 2;
        exec->groups = mem_realloc(exec->groups,
        sizeof(command_group_t) * exec->size,
        sizeof(command_group_t) * exec->capacity);
        if (exec->groups == NULL) return NULL;
    }

    command_group_t group = {
        .capacity = DEFAULT_GROUP_CAP,
        .size = 0,
        .commands = malloc(sizeof(command_t) * DEFAULT_GROUP_CAP)
    };
    if (group.commands == NULL) return NULL;
    exec->groups[exec->size] = group;
    exec->size++;

    return &exec->groups[exec->size - 1];
}

command_t *command_group_add_command(command_group_t *group)
{
    if (group->size == group->capacity) {
        group->capacity *= 2;
        group->commands = mem_realloc(group->commands,
        sizeof(command_t) * group->size,
        sizeof(command_t) * group->capacity);
        if (group->commands == NULL) return NULL;
    }
    command_args_t args = {
        .capacity = DEFAULT_ARGS_CAP,
        .size = 0,
        .argv = malloc(sizeof(char *) * DEFAULT_ARGS_CAP)
    };
    if (args.argv == NULL) return NULL;
    args.argv[0] = NULL;

    command_t command = {0};
    command.args = args;
    group->commands[group->size] = command;
    group->size++;
    return &group->commands[group->size - 1];
}

int command_push_arg(command_t *command, char *arg)
{
    if (command->args.size == command->args.capacity - 1) {
        command->args.capacity *= 2;
        command->args.argv = mem_realloc(command->args.argv,
        sizeof(char *) * (command->args.size + 1),
        sizeof(char *) * command->args.capacity);
        if (command->args.argv == NULL) return ERROR_RETURN;
    }
    command->args.argv[command->args.size] = arg;
    command->args.size++;
    command->args.argv[command->args.size] = NULL;

    return SUCCESS_RETURN;
}
