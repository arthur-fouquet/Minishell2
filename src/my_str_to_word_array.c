/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** my_str_to_word_array.c
*/

#include "my.h"

int nbr_back_n(char *str)
{
    int b = 1;
    int a = 0;

    for (; str[a] == '\t' || str[a] == ' ' || str[a] == '\n'; a++);
    for (; str[a] != '\0'; a++) {
        if ((str[a] == ' ' || str[a] == '\t' || str[a] == '\n') &&
            (str[a + 1] != ' ' && str[a + 1] != '\n' && str[a + 1] != '\t' &&
            str[a + 1] != '\0'))
            b++;
    }
    return (b);
}

int size_col(char  *str, int nbr)
{
    int count = 0;
    int a = 0;

    while (nbr != 0) {
        for (; str[a] == ' ' || str[a] == '\n' || str[a] == '\t'; a++);
        while (str[a] != ' ' && str[a] != '\0' && str[a] != '\t' &&
            str[a] != '\n')
            a++;
        nbr--;
    }
    for (; str[a] == ' ' || str[a] == '\n' || str[a] == '\t'; a++);
    while (str[a] != ' ' && str[a] != '\0' && str[a] != '\t' &&
        str[a] != '\n') {
        a++;
        count++;
    }
    return (count);
}

char **mallo(char *str)
{
    int count = nbr_back_n(str);
    char **tab = malloc(sizeof(char *) * (count + 1));

    if (tab == NULL)
        return NULL;
    for (int a = 0; a != count; a++) {
        tab[a] = malloc(sizeof(char) * (size_col(str, a) + 1));
        if (tab[a] == NULL)
            return NULL;
    }
    return (tab);
}

char **my_str_to_word_array(char *str)
{
    char **tab = mallo(str);
    int a = 0, b = 0, c = 0;

    if (tab == NULL)
        return NULL;
    for (; str[a] != '\0'; a++) {
        for (; str[a] == ' ' || str[a] == '\t' || str[a] == '\n'; a++);
        if (str[a] == '\0')
            break;
        for (; str[a] != ' ' && str[a] != '\0' && str[a] != '\t' &&
            str[a] != '\n'; c++, a++)
            tab[b][c] = str[a];
        tab[b][c] = '\0';
        b++;
        c = 0;
        if (str[a] == '\0')
            break;
    }
    tab[b] = NULL;
    return (tab);
}
