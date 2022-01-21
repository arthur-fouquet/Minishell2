/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** setenv_unsetenv.c
*/

#include "my.h"

int count_size_tab(char **tab)
{
    int a = 0;

    for (; tab[a] != NULL; a++);
    return (a);
}

void setenv_add_line(char **tab, char ***env, int count)
{
    char **new_env = malloc(sizeof(char *) * (count + 2));
    int a = 0;

    if (new_env == NULL)
        exit(84);
    for (; a != count; a++) {
        new_env[a] = malloc(sizeof(char) * (my_strlen((*env)[a]) + 1));
        if (new_env[a] == NULL)
            exit(84);
        new_env[a] = my_strcpy(new_env[a], (*env)[a]);
    }
    new_env[a] = re_mal(re_mal(tab[1], "=", 0), tab[2], 1);
    new_env[a + 1] = NULL;
    free_tab(*env);
    (*env) = new_env;
}

void setenv_modif_line(char **tab, char ***env, int pos)
{
    char *str = re_mal(re_mal(tab[1], "=", 0), tab[2], 1);

    free((*env)[pos]);
    (*env)[pos] = str;
}

void my_setenv(char **tab, char ***env)
{
    int count = 0;
    int add_line = 1;
    int pos = 0;

    if (setenv_condition(tab[1]) != 0)
        return;
    for (int a = 0; (*env)[a] != NULL; a++) {
        count++;
        if (my_strncmp_env(tab[1], (*env)[a], size_env_name((*env)[a])) == 0) {
            add_line = 0;
            pos = a;
        }
    }
    if (add_line == 1)
        setenv_add_line(tab, env, count);
    if (add_line == 0)
        setenv_modif_line(tab, env, pos);
}

int setenv_unsetenv(char **tab, char ***env)
{
    int size_tab = count_size_tab(tab);

    if (my_strcmp(tab[0], "setenv") == 0) {
        if (tab[1] == NULL) {
            env_fct((*env));
            return (1);
        }
        if (size_tab > 3) {
            write(1, "setenv: Too many arguments.\n", 28);
            return (1);
        }
        my_setenv(tab, env);
        return (1);
    }
    if (my_strcmp(tab[0], "unsetenv") == 0) {
        my_unsetenv(tab, env, size_tab);
        return (1);
    }
    return (0);
}
