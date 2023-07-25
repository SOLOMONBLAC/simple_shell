#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/* Function to execute a command in the shell */
int execute_command(char *command);

/* Function to handle the && and || logical operators in the shell */
int handle_logical_operators(char *input);

#endif /* SIMPLE_SHELL_H */

