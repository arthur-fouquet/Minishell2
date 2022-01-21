/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** free_tab.c
*/

#include "my.h"

void free_tab(char **tab)
{
    for (int a = 0; tab[a] != NULL; a++)
        free(tab[a]);
    free(tab);
    tab = NULL;
}

void free_node(node_t **node)
{
    node_t *freeable = NULL;

    if ((*node) == NULL)
        return;
    while ((*node)->prev != NULL)
        *node = (*node)->prev;
    while (*node != NULL) {
        freeable = *node;
        *node = (*node)->next;
        free(freeable->cmd);
        free(freeable);
    }
}

void free_in_whil(node_t **node, char **str)
{
    free_node(node);
    free(*str);
}
