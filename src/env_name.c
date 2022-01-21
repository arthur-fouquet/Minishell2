/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** env_name.c
*/

#include "my.h"

int strlen_host(char *str)
{
    int a = 0;

    for (; str[a] != '\0' && str[a] != '.'; a++);
    return (a);
}

void env_name_bis(char *pwd, char *home)
{
    int count = 0;
    int a = 0;

    write(1, " ", 1);
    if (my_strcmp(pwd, home) == 0)
        write(1, "~", 1);
    else {
        for (int b = 0; pwd[b] != '\0'; b++)
            if (pwd[b] == '/')
                count++;
        while (count != 0) {
            if (pwd[a] == '/')
                count--;
            a++;
        }
        for (; pwd[a] != '\0'; a++)
            write(1, &pwd[a], 1);
    }
    write(1, "]$ ", 3);
}

void env_name(char **env)
{
    char *user = get_env(env, "USER");
    char *hostname = get_env(env, "HOST");
    char *pwd = NULL;
    char *home = get_env(env, "HOME");

    if (env[0] == NULL) {
        write(1, "> ", 2);
        return;
    } write(1, "[", 1);
    if (user != NULL)
        write(1, user, my_strlen(user));
    write(1, "@", 1);
    if (hostname != NULL)
        write(1, hostname, strlen_host(hostname));
    pwd = getcwd(pwd, 0);
    env_name_bis(pwd, home);
    free(pwd);
    free(home);
    free(user);
    free(hostname);
}
