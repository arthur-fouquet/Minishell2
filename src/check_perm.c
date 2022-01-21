/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** chekc_perm.c
*/

#include "my.h"

int check_perm(char *str)
{
    if (access(str, F_OK) != 0)
        return (1);
    if (access(str, X_OK) != 0)
        return (2);
    return (0);
}
