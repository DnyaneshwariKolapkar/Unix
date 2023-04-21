#include <stdio.h>      // Include standard input/output library
#include <stdlib.h>     // Include standard library
#include <unistd.h>     // Include Unix standard library


// implementation of command ls | wc -l   (count the number of lines in the output of ls)

int main(void)          // Main function of the program
{
    int pfds[2];        // Integer array of size 2 to store file descriptors

    pipe(pfds);         // Create a pipe and store file descriptors in pfds array

    if (!fork()) {      // Child process
        close(1);                       // Close standard output (stdout)
        dup(pfds[1]);                   // Duplicate write end of pipe to stdout
        close(pfds[0]);                 // Close read end of pipe
        execlp("ls", "ls", NULL);       // Execute the "ls" command to list files in current directory
    } else {            // Parent process
        close(0);                       // Close standard input (stdin)
        dup(pfds[0]);                   // Duplicate read end of pipe to stdin
        close(pfds[1]);                 // Close write end of pipe
        execlp("wc", "wc", "-l", NULL); // Execute the "wc -l" command to count the number of lines
    }

    return 0;   // Exit program with a status code of 0 to indicate success
}
