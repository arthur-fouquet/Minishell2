/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** parse_command_bis.c
*/

#include "my.h"

int size_malloc(char *str, int start)
{
    int size = 0;

    for (int a = start; str[a] != ';' && str[a] != '|' && str[a] !=
        '\0' && str[a] != '<' && str[a] != '>' && str[a] != '\n'; a += 1) {
        if (str[a] != ' ' || (str[a] == ' ' && str[a + 1] != ' ' &&
            str[a + 1] != '\0' && str[a + 1] != ';' &&
            str[a + 1] != '|' && str[a + 1] != '<' &&
            str[a + 1] != '>' && str[a + 1] != '\n'))
            size++;
    }
    return (size);
}
