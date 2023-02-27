/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    /**
     * @brief Parsed command structure
     */
    typedef struct {
        char *path;
        char **args;
        char **parts;
    } sh_command_t;

    /**
     * @brief Parse a command
     *
     * @param command Command to parse
     * @return sh_command_t* Parsed command (NULL if error)
     */
    sh_command_t *sh_parse_command(char *command);

    /**
     * @brief Free a parsed command
     *
     * @param command Parsed command to free
     */
    void sh_command_free(sh_command_t *command);

#endif /* !COMMAND_H_ */
