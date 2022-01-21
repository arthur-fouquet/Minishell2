/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** get_next_line.c
*/

#include <stdlib.h>
#include <fcntl.h>
#include "my.h"

char *re_mallo(char *buffer, char *bis)
{
    int a = 0;
    char *str;

    if (bis == NULL)
        return buffer;
    if (buffer == NULL)
        return (NULL);
    for (; buffer[a] != '\0'; a++);
    for (int b = 0; bis[b] != '\0'; b++, a++);
    str = malloc(sizeof(char) * (a + 1));
    if (str == NULL)
        return (NULL);
    for (a = 0; buffer[a] != '\0'; a++)
        str[a] = buffer[a];
    for (int e = 0; bis[e] != '\0'; e++, a++)
        str[a] = bis[e];
    str[a] = '\0';
    free(buffer);
    free(bis);
    return (str);
}

static int check_buf(char *buffer, int *m)
{
    int cond = 0;
    int a = 0;

    if (buffer == NULL)
        return (2);
    if ((*m) == 1)
        return 1;
    for (; buffer[a] != '\0' && buffer[a] != '\n'; a++);
    if (buffer[a] == '\n')
        cond = 1;
    return (cond);
}

static char *read_fct(int fd, int *m)
{
    char *buffer = malloc(sizeof(char) * (READ_SIZE + 1));
    int val = 0;

    if (buffer == NULL)
        return (NULL);
    val = read(fd, buffer, READ_SIZE);
    if (val == -1)
        return (NULL);
    if (val == 0) {
        (*m) = 1;
        return NULL;
    }
    buffer[val] = '\0';
    (*m) = 0;
    return (buffer);
}

static char *fill_static(char *read_char, char **static_char, int a)
{
    char *str = malloc(sizeof(char) * (a + 1));
    int c = a;
    int size = 0;

    for (; read_char[a + 1] != '\0'; a++, size++);
    *static_char = malloc(sizeof(char) * (size + 1));
    if (str == NULL || (static_char) == NULL)
        return NULL;
    for (int b = 0; read_char[b] != '\n' && read_char[b] != '\0'; b++)
        str[b] = read_char[b];
    str[c] = '\0';
    for (int q = 0; read_char[c + 1] != '\0'; c++, q++)
        (*static_char)[q] = read_char[c + 1];
    (*static_char)[size] = '\0';
    if ((*static_char)[0] == '\0') {
        free((*static_char));
        (*static_char) = NULL;
    }
    return (str);
}

char *get_next_line(int fd)
{
    char *read_char;
    static char *static_char = NULL;
    static int m = 0;
    int a = 0;

    if (fd == -1 || READ_SIZE < 0)
        return (NULL);
    if (static_char != NULL) {
        read_char = static_char;
        static_char = NULL;
    } else
        read_char = read_fct(fd, &m);
    while (check_buf(read_char, &m) != 1 && check_buf(read_char, &m) != 2)
        read_char = re_mallo(read_char, read_fct(fd, &m));
    if (read_char == NULL)
        return (NULL);
    for (; read_char[a] != '\n' && read_char[a] != '\0'; a++);
    if (read_char[a] == '\n' && READ_SIZE != 1)
    read_char = fill_static(read_char, &static_char, a);
    return (read_char);
}
