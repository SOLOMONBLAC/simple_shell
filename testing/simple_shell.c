#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h> /* For open system call */
#include <dirent.h> /* For opendir and readdir system calls */
#include "shell.h" /* Include the custom header file */

#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100

int main() {
    char input[MAX_COMMAND_LENGTH];
    int result; /* Move the declaration of 'result' here */

    write(STDOUT_FILENO, "Enter commands separated by '&' or '|': ", strlen("Enter commands separated by '&' or '|': "));
    fgets(input, sizeof(input), stdin);

    result = handle_logical_operators(input); /* Now we can assign the value to 'result' */

    /* Output the final result of the logical operators */
    if (result) {
        write(STDOUT_FILENO, "All commands succeeded!\n", strlen("All commands succeeded!\n"));
    } else {
        write(STDOUT_FILENO, "Some commands failed!\n", strlen("Some commands failed!\n"));
    }

    return 0;
}

