/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** string
*/

#ifndef STRING_H_
    #define STRING_H_

    #include <stddef.h>

    /**
     * @brief Get the length of a string.
     *
     * @param str The string.
     * @return size_t The length of the string.
     */
    size_t str_len(const char *str);

    /**
     * @brief Get the length of a string until a specified character.
     *
     * @param str The string.
     * @param delimiter The delimiter (use '\0' to get the length of the
     * whole string).
     * @return size_t The length of the string.
     */
    size_t str_len_until(const char *str, char delimiter);

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
     * @brief Split a string on the specified delimiter and returns an array
     * of the parts.
     *
     * @param str The string to split.
     * @param delimiter The delimiter.
     * @return char** An array of the parts, ended by NULL (NULL if the
     * allocation failed).
     */
    char **str_split(const char *str, char delimiter);

    /**
     * @brief Split a string once on the specified delimiter and returns an
     * array of the two parts.
     *
     * @param str The string to split.
     * @param delimiter The delimiter.
     * @return char** An array of the two parts (NULL if the delimiter is not
     * found).
     */
    char **str_split_once(const char *str, char delimiter);

    /**
     * @brief Remove starting and ending spaces/newlines from a string.
     *
     * @param str The string to trim.
     * @return char* The trimmed string (NULL if the allocation failed).
     */
    char *str_trim(char *str);

#endif /* !STRING_H_ */
