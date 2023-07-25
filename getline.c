#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include <string.h>


#define BUFFER_SIZE 64

char* my_getline(void) {
    static char buffer[BUFFER_SIZE];
    static int buffer_index = 0;
    static int bytes_read = 0;
    char* line = NULL;
    int line_index = 0;
    char ch;
    int i; /* Move the declaration of 'i' to the beginning of the function */

    while (1) {
        if (buffer_index == bytes_read) {
            bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (bytes_read <= 0) {
                break;
            }
            buffer_index = 0;
        }

        ch = buffer[buffer_index++];

        if (ch == '\n') {
            line = (char*)malloc((line_index + 1) * sizeof(char));
            if (!line) {
                perror("Error allocating memory");
                return NULL;
            }
            for (i = 0; i < line_index; ++i) {
                line[i] = buffer[i];
            }
            line[i] = '\0';
            return line;
        }

        line = (char*)realloc(line, (line_index + 1) * sizeof(char));
        if (!line) {
            perror("Error reallocating memory");
            return NULL;
        }
        line[line_index++] = ch;
    }

    if (line) {
        line = (char*)realloc(line, (line_index + 1) * sizeof(char));
        if (!line) {
            perror("Error reallocating memory");
            return NULL;
        }
        line[line_index] = '\0';
    }

    return line;
}

int main() {
    char* line;

    while ((line = my_getline()) != NULL) {
        write(STDOUT_FILENO, "Line: ", 6);
        write(STDOUT_FILENO, line, strlen(line));
        write(STDOUT_FILENO, "\n", 1);
        free(line);
    }

    return 0;
}
