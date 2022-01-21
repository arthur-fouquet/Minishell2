/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** parser.c
*/

#include <fcntl.h>
#include "my.h"

static int retrn_value(char *str, int a)
{
    if (str[a + 1] == ' ') {
        if (str[a] == '<')
            return (2);
        return (3);
    } else if (str[a + 1] == '<' || str[a + 1] == '>') {
        if (str[a + 1] == '<')
            return (4);
        return (5);
    } else
        return (-1);
}

static char find_next_cmd(char *str, int a)
{
    for (; str[a] != '\0' && str[a] != ';' &&
        str[a] != '|' && str[a] != '<' && str[a] != '>'; a++);
    switch (str[a]) {
    case ';':
        return (0);
    case '|':
        return (1);
    case '<':
        return (retrn_value(str, a));
    case '>':
        return (retrn_value(str, a));
    default:
        return (0);
    }
}

static int fill_cmd(node_t **element, char *str, int start)
{
    int size = 0;

    for (int a = start; str[a] != ';' && str[a] != '|' && str[a] !=
        '\0' && str[a] != '<' && str[a] != '>' && str[a] != '\n'; a += 1) {
        if (str[a] != ' ' || (str[a] == ' ' && str[a + 1] != ' ' &&
            str[a + 1] != '\0' && str[a + 1] != ';' &&
            str[a + 1] != '|' && str[a + 1] != '<' &&
            str[a + 1] != '>' && str[a + 1] != '\n')) {
            (*element)->cmd[size] = str[a];
            size++;
        }
    }
    return (size);
}

static void add_node(node_t **node, char *str, int start)
{
    node_t *element = malloc(sizeof(node_t));
    int size = size_malloc(str, start);

    if (element == NULL)
        exit(84);
    element->cmd = malloc(sizeof(char) * (size + 1));
    if (element->cmd == NULL)
        exit(84);
    size = fill_cmd(&element, str, start);
    element->cmd[size] = '\0';
    if ((*node) == NULL)
        element->prev = NULL;
    else {
        while ((*node)->next != NULL)
            (*node) = (*node)->next;
        (*node)->next = element;
        element->prev = (*node);
    }
    element->next = NULL;
    (*node) = element;
}

void parser_cmd(char *str, node_t **node)
{
    int start = 0;

    for (int a = 0; str[a] != '\0'; a++) {
        for (; str[a] == ' ' || str[a] == '\t' || str[a] == '\n'; a++);
        if (str[a] == '\0')
            break;
        start = a;
        for (; str[a] != ';' && str[a] != '|' && str[a] != '\0' && str[a]
            != '<' && str[a] != '>' && str[a] != '\n'; a += 1);
        add_node(node, str, start);
        (*node)->cmd_next = find_next_cmd(str, start);
        for (; str[a] == ';' && str[a + 1] == ';'; a++);
        if ((str[a] == '|' && str[a + 1] == '|') ||
            (str[a] == '<' && str[a + 1] == '<') ||
            (str[a] == '>' && str[a + 1] == '>'))
            a++;
    }
    if ((*node))
        while ((*node)->prev != NULL)
            (*node) = (*node)->prev;
}
