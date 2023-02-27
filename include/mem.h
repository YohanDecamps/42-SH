/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** mem
*/

#ifndef MEM_H_
    #define MEM_H_

    #include <stddef.h>

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
     * @brief Free a null-terminated array of strings.
     *
     * @param array The array to free.
     */
    void mem_free_array(char **array);

#endif /* !MEM_H_ */
