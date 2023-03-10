/*
** EPITECH PROJECT, 2023
** shell
** File description:
** util
*/

#ifndef UTIL_H_
    #define UTIL_H_

    #include <stdbool.h>
    #include <stddef.h>

    /* STRING */

    /**
     * @brief Get the length of a string.
     *
     * @param str The string.
     * @return size_t The length of the string.
     */
    size_t str_len(const char *str);

    /**
     * @brief Get the length of a string until one of the specified characters.
     *
     * @param str The string.
     * @param delimiters The delimiters (use '\0' to get the length of the
     * whole string).
     * @return size_t The length of the string.
     */
    size_t str_len_until(const char *str, const char *delimiters);

    /**
     * @brief Allocates a copy of the specified string with the specified
     * length.
     *
     * @param str The string to copy.
     * @param len The length of the string to copy (use 0 to copy the whole
     * string).
     * @return char* The allocated copy of the string (NULL if the allocation
     * failed).
     */
    char *str_copy(const char *str, size_t len);

    /**
     * @brief Concatenate two strings with a separator.
     *
     * @param str1 First string.
     * @param str2 Second string.
     * @param sep The separator.
     * @return char* The concatenated string (NULL if the allocation failed).
     */
    char *str_concat(const char *str1, const char *str2, const char *sep);

    /**
     * @brief Compare two strings and returns an integer indicating their
     * order (-1 if str1 < str2, 0 if str1 == str2, 1 if str1 > str2).
     *
     * @param str1 First string to compare.
     * @param str2 Second string to compare.
     * @return int The result of the comparison.
     */
    int str_compare(const char *str1, const char *str2);

    /**
     * @brief Split a string on the specified delimiters and returns an array
     * of the parts.
     *
     * @param str The string to split.
     * @param delimiters List of delimiters
     * @return char** An array of the parts, ended by NULL (NULL if the
     * allocation failed).
     */
    char **str_split(const char *str, const char *delimiters);

    /**
     * @brief Split a string once on one of the specified delimiters and
     * returns an array of the two parts.
     *
     * @param str The string to split.
     * @param delimiters List of delimiters
     * @return char** An array of the two parts (NULL if the delimiter is not
     * found).
     */
    char **str_split_once(const char *str, const char *delimiter);

    /**
     * @brief Remove starting and ending spaces/newlines/tabs from a string.
     *
     * @param str The string to trim.
     * @return char* The trimmed string (NULL if the allocation failed).
     */
    char *str_trim(char *str);

    /**
     * @brief Check if a character is in the given list of characters.
     *
     * @param c The character to check.
     * @param list The list of characters.
     * @return bool true if the character is in the list, false otherwise.
     */
    bool str_char_in(char c, const char *list);

    /**
     * @brief Remove the ending newline of a string.
     *
     * @param str The string.
     */
    void str_remove_newline(char *str);

    /**
     * @brief Parse an int from a string.
     *
     * @param str The string to parse.
     * @param number Pointer to the variable that will contain the parsed
     * number.
     * @return int 0 if the parsing succeeded, -1 otherwise.
     */
    int str_parse_int(const char *str, int *number);

    /* MEMORY */

    /**
     * @brief Reallocate a memory block and copy the old content.
     *
     * @param ptr The memory block to reallocate.
     * @param old_size The old size of the memory block.
     * @param new_size The new size of the memory block.
     * @return void* The reallocated memory block (NULL if the allocation
     * failed).
     */
    void *mem_realloc(void *ptr, size_t old_size, size_t new_size);

    /**
     * @brief Get the length of a null-terminated array of strings.
     *
     * @param array The array.
     * @return size_t The length of the array.
     */
    size_t mem_array_len(char **array);

    /**
     * @brief Free a null-terminated array of strings.
     *
     * @param array The array to free.
     */
    void mem_free_array(char **array);

    /* PATH */

    /**
     * @brief Normalize a directory path by adding a trailing slash if
     * necessary.
     *
     * @param path The path to normalize.
     * @return char* The normalized path (NULL if the allocation failed).
     */
    char *normalize_directory(char *path);

    /**
     * @brief Expand a path by replacing '~' with the home directory.
     *
     * @param path The path to expand.
     * @return char* The expanded path (NULL if the allocation failed).
     */
    char *expand_home(char *path, char *home);

    /* ERROR */

    /**
     * @brief Print the error message corresponding to the specified error
     * code.
     *
     * @param prefix The prefix of the error message.
     * @param code The error code.
     */
    void print_error(const char *prefix, int code);

#endif /* !UTIL_H_ */
