/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** my_strncmp.c
*/

#include "my.h"

int my_strncmp(char *av, char *str, int n)
{
    int a = 0;

    for (; a != n && av[a] != '\0' && str[a] != '\0'; a++)
        if (str[a] != av[a])
            return (1);
    return (0);
}

int my_strncmp_env(char *tab, char *env, int size)
{
    int a = 0;

    for (; a != size && tab[a] != '\0' && env[a] != '\0'; a++)
        if (env[a] != tab[a])
            return (1);
    if (tab[a] != '\0')
        return (1);
    if (env[a] != '=')
        return (1);
    return (0);
}
