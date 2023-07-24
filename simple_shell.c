#include "shell.h"

#define MAX_COMMAND_LENGTH 100

void display_prompt() {
    write(STDOUT_FILENO, "$ ", 2);
}

int is_executable(char* command) {
    char path[MAX_COMMAND_LENGTH];
    if (access(command, X_OK) == 0) {
        /* Check if the file is executable */
        if (realpath(command, path) != NULL) {
            /* Update the command variable with the absolute path */
            strncpy(command, path, MAX_COMMAND_LENGTH - 1); /* Make sure to leave space for the null terminator */
            command[MAX_COMMAND_LENGTH - 1] = '\0'; /* Null-terminate the command */
            return 1;
        }
    }
    return 0;
}

void execute_command(char* command) {
    pid_t child_pid;
    if (!is_executable(command)) {
        write(STDOUT_FILENO, "Error: Command '", 16);
        write(STDOUT_FILENO, command, strlen(command));
        write(STDOUT_FILENO, "' not found.\n", 13);
        return;
    }

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        /* Child process */
        char* args[2];
        args[0] = command;
        args[1] = NULL;
        execve(command, args, NULL);
        perror("execve"); /* If execution reaches here, there was an error */
        _exit(EXIT_FAILURE);
    } else {
        /* Parent process */
        waitpid(child_pid, NULL, 0);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    ssize_t read_size;

    while (1) {
        display_prompt();

        read_size = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);
        if (read_size == -1) {
            perror("read");
            break;
        } else if (read_size == 0) {
            write(STDOUT_FILENO, "\nExiting the simple shell.\n", 26);
            break;
        }

        /* Remove the newline character from the command */
        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0) {
            continue;
        }

        execute_command(command);
    }

    return 0;
}
