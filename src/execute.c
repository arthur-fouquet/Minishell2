/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** execute.c
*/

#include "my.h"

void check_return_exec(int status)
{
    int return_value = 0;

    if (WIFEXITED(status)) {
        return_value = WEXITSTATUS(status);
    }
    if (WIFSIGNALED(status)) {
        return_value = WTERMSIG(status);
        if (return_value == 11)
            write(2, "Segmentation fault", 18);
        if (return_value == 6)
            write(2, "Abort", 5);
        if (return_value == 8)
            write(2, "Floating exception", 18);
        if (WCOREDUMP(status))
            write(2, " (core dumped)", 14);
        write(2, "\n", 1);
    }
}

void execute(char *exec, char **tab, char **env)
{
    pid_t c_pid = fork();
    pid_t waiter;
    int status = 0;

    if (c_pid == 0) {
        if (execve(exec, tab, env) == -1) {
            print_error(exec);
            exit(1);
        }
    } else if (c_pid > 0) {
        waiter = waitpid(c_pid, &status, 0);
        if (waiter < 0) {
            print_error(exec);
            exit(84);
        }
        check_return_exec(status);
    } else {
        print_error(exec);
        exit(84);
    }
}
