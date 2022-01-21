/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** my_getnbr.c
*/

#include "my.h"

int my_getnbr(char const *str)
{
    int nbr = 0;
    int i = 0;
    int sign = 1;

    for (; str[i] > '9' || str[i] < '0'; i++);
    if (i > 0) {
        if (str[i - 1] == '-')
            sign = -1;
    }
    for (; str[i] <= '9' && str[i] >= '0'; i++)
        nbr = nbr * 10 + (str[i] - '0');
    return (nbr * sign);
}
