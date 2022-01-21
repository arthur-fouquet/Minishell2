/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** redirections.c
*/

#include <fcntl.h>
#include "my.h"

void writ_in_file(char ***env, node_t **node)
{
    int cpy_stdout = dup(STDOUT_FILENO), fd = -1;

    if ((*node)->cmd[0] == '\0') {
        write(2, "Invalid null command.\n", 22);
        (*node) = (*node)->next;
        return;
    } if ((*node)->cmd_next == 3)
        fd = open((*node)->next->cmd, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
        S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if ((*node)->cmd_next == 5)
        fd = open((*node)->next->cmd, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR
        | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fd < 0) {
        write(2, "Error open.\n", 12);
        return;
    } dup2(fd, 1);
    close(fd);
    minishell(env, node);
    dup2(cpy_stdout, 1);
    *node = (*node)->next;
}

void read_from_file(char ***env, node_t **node)
{
    int fd = -1;
    int cpy_stdin = dup(0);

    if ((*node)->cmd[0] == '\0') {
        write(2, "Invalid null command.\n", 22);
        (*node) = (*node)->next;
        return;
    }
    fd = open((*node)->next->cmd, O_RDONLY);
    if (fd < 0) {
        print_error((*node)->next->cmd);
        (*node) = (*node)->next;
        return;
    }
    dup2(fd, 0);
    close(fd);
    minishell(env, node);
    dup2(cpy_stdin, 0);
    *node = (*node)->next;
}

char *file_str(char *param)
{
    char *str = malloc(1), *rd = NULL;
    size_t size = 0;
    int a = 0;

    if (str == NULL)
        return (NULL);
    str[0] = '\0';
    while (1) {
        write(1, "> ", 2);
        getline(&rd, &size, stdin);
        for (a = 0; rd[a] != '\n'; a++);
        rd[a] = '\0';
        if (my_strncmp(rd, param, my_strlen(param)) == 0) {
            free(rd);
            break;
        } rd = re_mal(rd, "\n", 1);
        str = re_mal(str, rd, 1);
        free(rd);
        rd = NULL;
    } return (str);
}

void double_redirect(char ***env, node_t **node)
{
    char *str = file_str((*node)->next->cmd);
    int cpy_stdin = dup(0);
    int fd = open("/tmp/redirect", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
        S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

    if (fd < 0) {
        write(2, "Error open.\n", 12);
        return;
    } write(fd, str, my_strlen(str));
    close(fd);
    if ((fd = open("/tmp/redirect", O_RDONLY)) < 0) {
        write(2, "Error open.\n", 12);
        return;
    }
    dup2(fd, 0);
    close(fd);
    minishell(env, node);
    dup2(cpy_stdin, 0);
    free(str);
    *node = (*node)->next;
}
