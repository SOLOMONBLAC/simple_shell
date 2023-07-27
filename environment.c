#include <stdio.h>
#include <unistd.h>
#include "shell.h"

extern char **environ;

void env() {
    char **env = environ;
    while (*env) {
        size_t len = 0;
        while ((*env)[len] != '\0') {
            len++;
        }
        write(STDOUT_FILENO, *env, len);
        write(STDOUT_FILENO, "\n", 1);
        env++;
    }
}

int main() {
    env();
    return 0;
}
