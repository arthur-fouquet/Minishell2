/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** shell.c
*/

#include "my.h"

char ***save_env(char ***env)
{
    static char ***copy = NULL;

    if (env != NULL)
        copy = env;
    return (copy);
}

void siginthandler(int sig)
{
    (void) sig;
    signal(SIGINT, siginthandler);
    write(1, "\n", 1);
    env_name(*save_env(NULL));
}

void shell(char **envp)
{
    char **env = copy_envp(envp);
    node_t *node = NULL;
    void *first = NULL;
    char *str = NULL;

    save_env(&env);
    signal(SIGINT, siginthandler);
    while (1) {
        if (isatty(0) != 0)
            env_name(env);
        str = get_next_line(0);
        if (str == NULL)
            break;
        parser_cmd(str, &node);
        first = node;
        exec_order(&env, &node);
        node = first;
        free_in_whil(&node, &str);
    } free_tab(env);
    free(str);
}
