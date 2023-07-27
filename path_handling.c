#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include "shell.h"

/* Function prototype for my_strdup() */
char *my_strdup(const char *str);

/* Function prototype for command_exists() */
int command_exists(const char *command);

/* Function to duplicate a string */
char *my_strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *dup = (char *)malloc(len);
    if (dup != NULL) {
        strcpy(dup, str);
    }
    return dup;
}

/* Function to check if the given command exists in the PATH */
int command_exists(const char *command) {
    char *path_env = getenv("PATH");
    char *path_copy;
    char *path;
    char *dir;
    char buffer[1024]; /* Move variable declaration to the beginning */

    if (!path_env) {
        return 0;
    }

    path_copy = my_strdup(path_env); /* Use my_strdup() instead of strdup() */
    path = path_copy;

    while ((dir = strtok(path, ":")) != NULL) {
        snprintf(buffer, sizeof(buffer), "%s/%s", dir, command);
        if (access(buffer, X_OK) == 0) {
            free(path_copy);
            return 1;
        }
        path = NULL;
    }

    free(path_copy);
    return 0;
}
