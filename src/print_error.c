/*
** EPITECH PROJECT, 2020
** PSU_minishll2_2019
** File description:
** print_error.c
*/

#include "my.h"

void print_error(char *str)
{
    write(2, str, my_strlen(str));
    write(2, ": ", 2);
    write(2, strerror(errno), my_strlen(strerror(errno)));
    if (errno == ENOEXEC)
        write(2, ". Wrong Architecture", 20);
    write(2, ".\n", 2);
}
