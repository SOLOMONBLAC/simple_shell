#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define BUF_FLUSH '\0'
#define WRITE_BUF_SIZE 1024

void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

void _eputs(char *str)
{
    int i = 0;
    char c;

    if (!str)
        return;

    while ((c = str[i]) != '\0')
    {
        _eputchar(c);
        i++;
    }
}

int _eputchar(char c)
{
    static int i = 0;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

int _putfd(char c, int fd)
{
    static int i = 0;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

int _putsfd(char *str, int fd)
{
    int i = 0;
    char c;

    if (!str)
        return (0);

    while ((c = *str++) != '\0')
    {
        i += _putfd(c, fd);
    }
    return (i);
}

#endif /* SHELL_H */

