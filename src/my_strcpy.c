/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** my_strcpy.c
*/

#include "my.h"

char *my_strcpy(char *dest, char *src)
{
    int a = 0;

    for (; src[a] != '\0'; a++)
        dest[a] = src[a];
    dest[a] = '\0';
    return (dest);
}
