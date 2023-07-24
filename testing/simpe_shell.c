#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int executeCommand(const char *command, char *const arguments[]) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");

    /* Declare the variable error_msg at the beginning */
    const char *error_msg = "execvp failed.\n";

    while (dir) {
        char cmd_path[256];
        snprintf(cmd_path, sizeof(cmd_path), "%s/%s", dir, command);

        /* Check if the command file exists in this directory */
        if (access(cmd_path, X_OK) == 0) {
            /* Command found, execute it using execvp */
            execvp(cmd_path, arguments);
            
            /* If execvp returns, it means an error occurred */
            write(1, error_msg, strlen(error_msg));
            free(path_copy);
            return -1;
        }

        dir = strtok(NULL, ":");
    }

    /* If the command wasn't found in any of the directories, free the memory and return an error */
    free(path_copy);
    return -1;
}

