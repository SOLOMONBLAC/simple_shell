#include <unistd.h>
#include <string.h>
#include  "shell1.h"

/* Function to handle command-line arguments */ void handle_arguments(int argc, char *argv[]){
    if (argc > 1) {
        char newline = '\n';
        char space = ' ';
        char *message = "Arguments provided:\n";
        int i; /* Move the declaration to the beginning of the block */
        write(1, message, strlen(message));
        for (i = 1; i < argc; i++) {
            write(1, argv[i], strlen(argv[i]));
            write(1, &space, 1);
        }
        write(1, &newline, 1);
    } else {
        char *message = "No arguments provided.\n";
        write(1, message, strlen(message));
    }
}

int main(int argc, char *argv[]) {
    handle_arguments(argc, argv);
    return 0;
}
