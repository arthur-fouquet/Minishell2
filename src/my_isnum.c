/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** my_isnum.c
*/

#include "my.h"

int my_isnum(char *av)
{
    int b = 0;
    if (av == NULL)
        return (84);
    if (av[0] == 0)
        return (84);
    if (av[0] == '-')
        b++;
    for (; av[b] != '\0'; b++)
        if (av[b] < '0' || av[b] > '9')
            return (84);
    return (0);
}
