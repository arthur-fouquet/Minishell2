/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** my_revstr.c
*/

#include "my.h"

char *my_revstr(char *str)
{
    int nb_letter = 0;
    int t = 0;

    for (; str[nb_letter] != '\0'; nb_letter++);
    nb_letter--;
    for (int a = 0; a < nb_letter; a++) {
        t = str[nb_letter];
        str[nb_letter] = str[a];
        str[a] = t;
        nb_letter--;
    }
    return (str);
}
