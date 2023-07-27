#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100

void execute_command(char *command) {
    int len;
    int num_args = 0;
    char *args[MAX_COMMAND_LENGTH];
    char *token;
    pid_t pid;

    /* Remove leading and trailing whitespaces */
    while (*command == ' ') {
        command++;
    }

    len = strlen(command);
    while (len > 0 && command[len - 1] == ' ') {
        command[--len] = '\0';
    }

    /* Tokenize the command to separate arguments */
    token = strtok(command, " ");
    while (token != NULL && num_args < MAX_COMMAND_LENGTH - 1) {
        args[num_args++] = token;
        token = strtok(NULL, " ");
    }
    args[num_args] = NULL;

    /* Fork to create a child process */
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
    } else if (pid == 0) {
        /* Child process: execute the command */
        execvp(args[0], args);
        perror("Exec failed");
        _exit(1);
    } else {
        /* Parent process: wait for the child to finish */
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char input[MAX_COMMAND_LENGTH];
    char *commands[MAX_COMMANDS];
    int num_commands = 0;
    char *token;
    int i;

    write(STDOUT_FILENO, "$ ", strlen("$ "));
    fgets(input, sizeof(input), stdin);

    /* Tokenize the input string based on ';' delimiter */
    token = strtok(input, ";");
    while (token != NULL && num_commands < MAX_COMMANDS) {
        commands[num_commands++] = token;
        token = strtok(NULL, ";");
    }

    /* Execute each command */
    for (i = 0; i < num_commands; i++) {
        execute_command(commands[i]);
    }

    return 0;
}
