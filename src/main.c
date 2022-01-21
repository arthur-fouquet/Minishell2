/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** main.c
*/

#include "my.h"

int main(int ac, char **av, char **env)
{
    if (ac != 1)
        return (84);
    (void) av;
    (void) av;
    shell(env);
    return (0);
}
