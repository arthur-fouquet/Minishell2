/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** copy_envp.c
*/

#include "my.h"

char **copy_envp(char **envp)
{
    int a = count_size_tab(envp);
    char **tab = malloc(sizeof(char *) * (a + 1));
    int b = 0;

    if (tab == NULL)
        exit(84);
    for (; b != a; b++) {
        tab[b] = malloc(sizeof(char) * (my_strlen(envp[b]) + 1));
        if (tab[b] == NULL)
            exit(84);
        tab[b] = my_strcpy(tab[b], envp[b]);
    }
    tab[b] = NULL;
    return (tab);
}
