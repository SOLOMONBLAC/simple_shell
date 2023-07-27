#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define MAX_INPUT_LENGTH 100

/* Function prototypes */
void display_prompt();
int is_executable(char* command);
void execute_command(char* command);
void handle_arguments(int argc, char *argv[]);
void exit_shell();
void handle_command(const char* input);
void run_shell();
void env();
char* my_getline(void);
int executeCommand(const char *command, char *const arguments[]);
void exit_with_status(int status);
int cd_command(const char *directory);
void execute_command(char *command);

#endif /* SHELL_H */
