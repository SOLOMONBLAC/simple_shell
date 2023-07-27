#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 100

void exit_with_status(int status) {
    exit(status);
}

int main() {
    char input[MAX_INPUT_LENGTH];
    int status;
    ssize_t bytes_written;
    char output[MAX_INPUT_LENGTH + 4]; /* Increased buffer size to accommodate prompt */

    while (1) {
        /* Using the write function to print the message to the standard output (file descriptor 1) */
        bytes_written = write(1, "$ ", 2);
        if (bytes_written == -1) {
            perror("Error writing to standard output");
            return 1;
        }

        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            /* Error handling if input is not read properly */
            perror("Failed to read input");
            return 1;
        }

        input[strcspn(input, "\n")] = '\0';

        if (sscanf(input, "exit %d", &status) == 1) {
            break;
        }

        /* Add your code to process other commands here */

        /* If the command is not "exit" or any other special command,
           you can execute other operations here */
    }

    /* Print the exit status after the shell terminates */
    snprintf(output, sizeof(output), "$ %s\n", input);
    /* Using the write function to print output */
    bytes_written = write(1, output, strlen(output));
    if (bytes_written == -1) {
        perror("Error writing to standard output");
        return 1;
    }

    snprintf(output, sizeof(output), "$?\n%d\n", status);
    /* Using the write function to print output */
    bytes_written = write(1, output, strlen(output));
    if (bytes_written == -1) {
        perror("Error writing to standard output");
        return 1;
    }

    exit_with_status(status);
    return 0;
}
