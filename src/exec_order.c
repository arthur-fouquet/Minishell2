/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** exec_order.c
*/

#include <memory.h>
#include "my.h"

static void exec_pipe(char ***env, node_t **node, int in_fd);

static void redirect(int oldfd, int newfd)
{
    if (oldfd != newfd) {
        if (dup2(oldfd, newfd) != -1)
            close(oldfd);
        else
            exit(84);
    }
}

static void child_father(int fd[2], char ***env, node_t **node, int in_fd)
{
    int status = 0;

    switch (fork()) {
    case -1:
        write(2, strerror(errno), my_strlen(strerror(errno)));
        exit(84);
    case 0:
        close(fd[0]);
        redirect(in_fd, STDIN_FILENO);
        redirect(fd[1], STDOUT_FILENO);
        minishell(env, node);
        exit(0);
    default:
        close(fd[1]);
        close(in_fd);
        *node = (*node)->next;
        exec_pipe(env, node, fd[0]);
        waitpid(in_fd, &status, 0);
    }
}

static void exec_pipe(char ***env, node_t **node, int in_fd)
{
    int fd[2];
    int aaa = dup(0);

    if ((*node)->next == NULL || (*node)->cmd_next != 1) {
        redirect(in_fd, STDIN_FILENO);
        minishell(env, node);
    } else {
        if (pipe(fd) == -1) {
            write(2, strerror(errno), my_strlen(strerror(errno)));
            exit(84);
        }
        child_father(fd, env, node, in_fd);
    }
    dup2(aaa, 0);
}

static int check_redirections(node_t **node)
{
    void *first = (*node);

    while (*node != NULL) {
        if ((*node)->cmd == NULL)
            return (84);
        if ((*node)->cmd_next == 1 && ((*node)->cmd[0] == '\0' ||
            (*node)->next == NULL || (*node)->next->cmd[0] == '\0')) {
            write(2, "Invalid null command.\n", 22);
            return (84);
        }
        if ((*node)->cmd_next != 0 && (*node)->cmd_next != 1 &&
            (*node)->cmd_next == (*node)->next->cmd_next) {
            write(2, "Ambiguous input redirect.\n", 26);
            return (84);
        }
        *node = (*node)->next;
    }
    (*node) = first;
    return (0);
}

void exec_order(char ***env, node_t **node)
{
    if (check_redirections(node) == 84)
        return;
    while (*node != NULL) {
        if ((*node)->cmd_next == -1)
            write(2, "Missing name for redirect.\n", 27);
        if ((*node)->cmd_next == 0)//;
            minishell(env, node);
        if ((*node)->cmd_next == 1)//|
            exec_pipe(env, node, STDIN_FILENO);
        if ((*node)->cmd_next == 2)//<
            read_from_file(env, node);
        if (((*node)->cmd_next == 3 || (*node)->cmd_next == 5))//>
            writ_in_file(env, node);
        if ((*node)->cmd_next == 4)//<<
            double_redirect(env, node);
        *node = (*node)->next;
    }
}
