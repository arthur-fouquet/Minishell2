/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** get_env.c
*/

#include "my.h"

int compar(char *env, char *elem)
{
    int size = my_strlen(elem);
    int count = 0;
    int w = 0;

    for (; env[w] != '\0' && elem[w] != '\0' && env[w] != '='; w++)
        if (env[w] == elem[w])
            count += 1;
    if (count == size && env[w] == '=')
        return (1);
    return (0);
}

char *get_env(char **env, char *elem)
{
    int a = 0;
    int b = 1;
    char *str = NULL;
    int f = 0;

    for (; env[a] != NULL; a++)
        if (compar(env[a], elem) == 1)
            break;
    if (env[a] == NULL)
        return (NULL);
    str = malloc(sizeof(char) * (my_strlen(env[a]) - my_strlen(elem) + 1));
    if (str == NULL)
        return (NULL);
    for (; env[a][b - 1] != '='; b++);
    for (; f != my_strlen(env[a]) - my_strlen(elem); f++, b++)
        str[f] = env[a][b];
    str[f] = '\0';
    return (str);
}
