/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** check_orders.c
*/

#include "my.h"

void exit_fct(char **tab, char ***env, node_t **node)
{
    int nbr = 0;
    unsigned char char_nbr = 0;

    if (tab[1] == NULL) {
        free_tab(tab);
        free_tab(*env);
        free_node(node);
        write(1, "exit\n", 5);
        exit(0);
    }
    if (my_isnum(tab[1]) == 0) {
        nbr = my_getnbr(tab[1]);
        char_nbr = nbr;
        free_tab(*env);
        free_tab(tab);
        write(1, "exit\n", 5);
        exit(char_nbr);
    }
    write(2, tab[0], my_strlen(tab[0]));
    write(2, ": Expression Syntax.\n", 21);
}

void env_fct(char **env)
{
    for (int a = 0; env[a] != NULL; a++) {
        write(1, env[a], my_strlen(env[a]));
        write(1, "\n", 1);
    }
}

void cd_fct(char **tab, char ***env)
{
    if (count_size_tab(tab) > 2) {
        write(1, "cd: Too many agruments.\n", 24);
        return;
    }
    if (tab[1] != NULL) {
        cd(env, tab[1]);
        return;
    }
    if (tab[1] == NULL)
        cd(env, NULL);
}

int check_orders(char **tab, char ***env, node_t **node)
{
    if (tab[0] == NULL)
        return 1;
    if (my_strncmp(tab[0], "exit", 4) == 0 && my_strlen(tab[0]) == 4) {
        exit_fct(tab, env, node);
        return (1);
    }
    if (my_strcmp(tab[0], "env") == 0) {
        env_fct(*env);
        return (1);
    }
    if (my_strcmp(tab[0], "cd") == 0) {
        cd_fct(tab, env);
        return (1);
    }
    if (setenv_unsetenv(tab, env) == 1)
        return (1);
    return (0);
}
