/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** path_to_word_array.c
*/

#include "my.h"

int nbr_double_coma(char *str)
{
    int a = 1;

    if (str == NULL)
        return (0);
    for (int q = 0; str[q] != '\0'; q++)
        if (str[q] == ':')
            a++;
    return (a);
}

int size_path(char  *str, int nbr)
{
    int count = 0;
    int a = 0;

    while (nbr != 0) {
        while (str[a] != ':' && str[a] != '\0')
            a++;
        if (str[a])
            a += 1;
        nbr--;
    }
    while (str[a] != ':' && str[a] != '\0') {
        a++;
        count++;
    }
    return (count);
}

char **create_tab(char *str)
{
    int count = nbr_double_coma(str);
    char **tab = malloc(sizeof(char *) * (count + 1));

    if (tab == NULL)
        return NULL;
    for (int a = 0; a != count; a++) {
        tab[a] = malloc(sizeof(char) * (size_path(str, a) + 1));
        if (tab[a] == NULL)
            return NULL;
    }
    return (tab);
}

char **path_to_word_array(char *str)
{
    char **tab = create_tab(str);
    int a = 0;
    int b = 0;
    int c = 0;

    if (tab == NULL || str == NULL)
        return NULL;
    for (; str[a] != '\0'; a++, b++) {
        for (c = 0; str[a] != ':' && str[a] != '\0'; c++) {
            tab[b][c] = str[a];
            a++;
        }
        tab[b][c] = '\0';
        if (str[a] == '\0')
            break;
    }
    tab[b + (str[a] == '\0')] = NULL;
    return (tab);
}
