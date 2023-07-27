#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#define PATH_MAX 4096

/* Implement the builtin command cd:
   Changes the current directory of the process.
   Command syntax: cd [DIRECTORY]
   If no argument is given to cd, the command must be interpreted like cd $HOME
   You have to handle the command cd -
   You have to update the environment variable PWD when you change directory
   man chdir, man getcwd */

int cd_command(const char *directory) {
    char *new_dir;
    char current_dir[PATH_MAX];  /* Declare current_dir here */

    /* If no argument is given, use the home directory */
    if (directory == NULL) {
        new_dir = getenv("HOME");
        if (new_dir == NULL) {
            perror("cd");
            return 1;
        }
    } else if (strcmp(directory, "-") == 0) {
        /* Handle 'cd -' to return to the previous directory */
        new_dir = getenv("OLDPWD");
        if (new_dir == NULL) {
            perror("cd");
            return 1;
        }
        write(STDOUT_FILENO, new_dir, strlen(new_dir));
        write(STDOUT_FILENO, "\n", 1);
    } else {
        /* Use the provided directory argument */
        new_dir = (char *)directory;
    }

    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("cd");
        return 1;
    }

    /* Change the directory using chdir() */
    if (chdir(new_dir) != 0) {
        perror("cd");
        return 1;
    }

    /* Update the environment variable PWD */
    if (setenv("PWD", new_dir, 1) != 0) {
        perror("cd");
        return 1;
    }

    /* Update the environment variable OLDPWD with the previous directory */
    if (setenv("OLDPWD", current_dir, 1) != 0) {
        perror("cd");
        return 1;
    }

    return 0;
}

int main() {
    /* Example usage of the cd_command function */
    if (cd_command("/path/to/directory") != 0) {
        write(STDOUT_FILENO, "cd: Failed to change directory.\n", strlen("cd: Failed to change directory.\n"));
        return 1;
    }

    /* Test 'cd -' */
    if (cd_command("-") != 0) {
        write(STDOUT_FILENO, "cd: Failed to change directory.\n", strlen("cd: Failed to change directory.\n"));
        return 1;
    }

    return 0;
}
