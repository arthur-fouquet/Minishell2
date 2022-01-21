/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** minishell.c
*/

#include "my.h"

void print_perm(int perm, char *str)
{
    if (perm == 1) {
        write(2, str, my_strlen(str));
        write(2, ": Command not found.\n", 21);
    }
    if (perm == 2) {
        write(2, str, my_strlen(str));
        write(2, ": Permission denied.\n", 21);
    }
}

char *find_fill_perm(char **tab, char **envi)
{
    char *str = NULL;
    int w = 0;
    int perm = check_perm(tab[0]);

    if (perm == 0)
        return (tab[0]);
    if (tab[0][0] == '.' && tab[0][1] == '/') {
        print_perm(perm, tab[0]);
        return (NULL);
    }
    env_exec(&envi, tab[0]);
    for (; envi[w] != NULL; w++) {
        perm = check_perm(envi[w]);
        if (perm == 0) {
            str = envi[w];
            break;
        }
    } if (str == NULL)
        print_perm(perm, tab);
    return (str);
}

char *get_exec(char **env, char **tab)
{
    char **envi = NULL;
    char *return_str = NULL;
    char *str = get_env(env, "PATH");

    envi = path_to_word_array(str);
    free(str);
    if (envi == NULL) {
        write(2, tab[0], my_strlen(tab[0]));
        write(2, ": Command not found.\n", 21);
        return (NULL);
    }
    return_str = find_fill_perm(tab, envi);
    for (int a = 0; envi[a] != NULL; a++)
        if (envi[a] != return_str)
            free(envi[a]);
    free(envi);
    return (return_str);
}

void minishell(char ***env, node_t **node)
{
    char *exec = NULL;
    char **tab = NULL;
    int returned = 0;

    tab = my_str_to_word_array((*node)->cmd);
    if (tab == NULL || tab[0] == NULL)
        returned = 1;
    returned = check_orders(tab, env, node);
    if (returned == 0)
        exec = get_exec(*env, tab);
    if (exec != NULL && returned == 0)
        execute(exec, tab, *env);
    if (my_strcmp(tab[0], exec) != 0)
        free(exec);
    free_tab(tab);
}
