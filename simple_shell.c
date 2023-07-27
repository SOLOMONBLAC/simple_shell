#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int main() {
    const char *command = "ls";  /* Replace this with the desired command */
    char *const arguments[] = {"ls", "-l", NULL};  /* Replace this with arguments if needed */

    int result = executeCommand(command, arguments);
    if (result == -1) {
        const char *error_msg = "Command not found or execution failed.\n";
        write(1, error_msg, strlen(error_msg));
    }

    return 0;
}
