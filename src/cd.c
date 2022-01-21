/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** cd.c
*/

#include "my.h"

static void shift_str(char **str)
{
    int a = 0;

    for (; (*str)[a + 1] != '\0'; a++)
        (*str)[a] = (*str)[a + 1];
    (*str)[a] = '\0';
}

static void check_str(char ***env, char **str, int *free_or_not)
{
    char *arg = NULL;

    if ((*str)[0] == '~') {
        (*free_or_not) = 1;
        arg = get_env((*env), "HOME");
        if (arg == NULL) {
            write(2, "cd: No home directory.\n", 23);
            return;
        }
        shift_str(str);
        (*str) = re_mal(arg, (*str), 1);
    } if ((*str)[0] == '-') {
        (*free_or_not) = 1;
        arg = get_env((*env), "OLDPWD");
        if (arg == NULL) {
            write(2, ": No such file or directory.\n", 29);
            return;
        } shift_str(str);
        (*str) = re_mal(arg, (*str), 1);
    }
}

void free_cd(char *pwd, char *pwd_bis, char *str, int free_str_or_not)
{
    if (free_str_or_not == 1)
        free(str);
    free(pwd);
    free(pwd_bis);
}

void cd(char ***env, char *str)
{
    char *pwd = NULL;
    char *pwd_bis = NULL;
    char *tab_old[3] = {"setenv", "OLDPWD", NULL};
    char *tab_bis[3] = {"setenv", "PWD", NULL};
    int free_str_or_not = 0;

    pwd = getcwd(pwd, 0);
    tab_old[2] = pwd;
    if (str == NULL) {
        str = get_env((*env), "HOME");
        free_str_or_not = 1;
    } check_str(env, &str, &free_str_or_not);
    if (chdir(str) == -1) {
        print_error(str);
        return;
    } my_setenv(tab_old, env);
    pwd_bis = getcwd(pwd_bis, 0);
    tab_bis[2] = pwd_bis;
    my_setenv(tab_bis, env);
    free_cd(pwd, pwd_bis, str, free_str_or_not);
}
