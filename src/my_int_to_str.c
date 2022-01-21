/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** my_int_to_str.c
*/

#include "my.h"

int counter(int d)
{
    int i = 0;

    for (; d != 0; i++)
        d = d / 10;
    return (i);
}

char *my_int_to_str(int nb)
{
    char *str;
    int i = 0;
    int a = 0;

    if (nb == 0) {
        str = malloc(sizeof(char) * 2);
        str = "0";
        return (str);
    }
    i = counter(nb);
    str = malloc(sizeof(char) * (i + 1));
    for (; i != 0;) {
        str[a] = (nb % 10) + '0';
        nb = nb / 10;
        a++;
        i--;
    }
    str[a] = '\0';
    str = my_revstr(str);
    return (str);
}
