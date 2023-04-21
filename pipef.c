#include <stdio.h>      // Include standard input/output library
#include <stdlib.h>     // Include standard library
#include <errno.h>      // Include error library
#include <sys/types.h>  // Include system types library
#include <unistd.h>     // Include Unix standard library


/* program creates a pipe using the pipe() function and then forks the process 
using the fork() function. The child process writes the string "test" to the 
write end of the pipe using the write() function and then exits using the exit() 
function. The parent process reads data from the read end of the pipe using the 
read() function and prints the data that was read to the console using the printf() 
function. The wait() function is used to wait for the child process to complete before 
the parent process exits.
*/

int main(void)          // Main function of the program
{
    int pfds[2];        // Integer array of size 2 to store file descriptors
    char buf[30];       // Character array of size 30 to store data

    pipe(pfds);         // Create a pipe and store file descriptors in pfds array

    if (!fork()) {      // Child process
        printf(" CHILD: writing to the pipe\n");   // Print message indicating that child is writing to pipe
        write(pfds[1], "test", 5);                // Write data to write end of pipe
        printf(" CHILD: exiting\n");              // Print message indicating that child is exiting
        exit(0);        // Exit child process with a status code of 0 to indicate success
    } else {            // Parent process
        printf("PARENT: reading from pipe\n");    // Print message indicating that parent is reading from pipe
        read(pfds[0], buf, 5);                    // Read data from read end of pipe
        printf("PARENT: read \"%s\"\n", buf);     // Print data that was read from pipe
        wait(NULL);     // Wait for child process to complete
    }

    return 0;   // Exit program with a status code of 0 to indicate success
}
