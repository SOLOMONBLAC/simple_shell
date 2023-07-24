#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"

#define MAX_INPUT_LENGTH 100

void exit_shell() {
    const char exit_message[] = "Exiting the shell...\n";
    write(STDOUT_FILENO, exit_message, sizeof(exit_message) - 1);
    exit(0);
}

void handle_command(const char* input) {
    const char newline[] = "\n"; 
    if (strcmp(input, "exit") == 0) {
        exit_shell();
    } else {
        const char not_recognized_message[] = "Command not recognized: ";
        write(STDOUT_FILENO, not_recognized_message, sizeof(not_recognized_message) - 1);
        write(STDOUT_FILENO, input, strlen(input));
        write(STDOUT_FILENO, newline, sizeof(newline) - 1);
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    const char prompt[] = "$ ";

    while (1) {
        write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);

        fgets(input, MAX_INPUT_LENGTH, stdin);

        input[strcspn(input, "\n")] = '\0';

        handle_command(input);
    }

    return 0;
}
