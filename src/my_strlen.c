/*
** EPITECH PROJECT, 2020
** CPE_minishell2_2019
** File description:
** my_strlen.c
*/

#include "my.h"

int my_strlen(char *str)
{
    int a = 0;

    if (str == NULL)
        return 0;
    for (; str[a] != '\0'; a++);
    return (a);
}
