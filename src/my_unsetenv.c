/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** my_unsetenv.c
*/

#include "my.h"

int size_env_name(char *env)
{
    int a = 0;

    for (; env[a] != '\0' && env[a] != '='; a += 1);
    return (a);
}

void unset(char ***env, int count, int size)
{
    char **str = malloc(sizeof(char *) * count);
    int b = 0;
    int a = 0;

    for (; a != count - 1; a++, b++) {
        if (a == size)
            b++;
        str[a] = malloc(sizeof(char) * (my_strlen((*env)[b]) + 1));
        if (str[a] == NULL)
            exit(84);
        str[a] = my_strcpy(str[a], (*env)[b]);
    }
    str[a] = NULL;
    free_tab(*env);
    (*env) = str;
}

int check_rm(char **env, char *tab)
{
    for (int a = 0; env[a] != NULL; a++)
        if (my_strncmp_env(tab, env[a], size_env_name(env[a])) == 0)
            return (a);
    return (-1);
}

void my_unsetenv(char **tab, char ***env, int size_tab)
{
    int count = 0;
    int size = 0;

    if (size_tab < 2) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return;
    }
    for (int a = 1; tab[a] != NULL; a++) {
        size = check_rm((*env), tab[a]);
        if (size != -1) {
            for (; (*env)[count] != NULL; count++);
            unset(env, count, size);
            count = 0;
        }
    }
}
