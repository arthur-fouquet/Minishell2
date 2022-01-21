/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** setenv_condition.c
*/

#include "my.h"

int is_num(char c)
{
    if (c <= '9' && c >= '0')
        return 0;
    return 1;
}

int is_letter(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (0);
    if (c >= 'a' && c <= 'z')
        return (0);
    return 1;
}

int setenv_condition(char *tab)
{
    if ((tab[0] > 'Z' || tab[0] < 'A') && (tab[0] < 'a' || tab[0] > 'z')) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return (1);
    }
    for (int a = 0; tab[a] != '\0'; a++)
        if (is_num(tab[a]) != 0 && is_letter(tab[a]) != 0) {
            write(2, "setenv: Variable name must contain alphanumeric", 47);
            write(2, " characters.\n", 13);
            return (1);
        }
    return (0);
}
