#include <stdio.h>      // Include standard input/output library
#include <stdlib.h>     // Include standard library
#include <errno.h>      // Include error library
#include <unistd.h>     // Include Unix standard library

/*program creates a pipe using the pipe() function and then writes the string "test" 
to the write end of the pipe using the write() function. It then reads data from the 
read end of the pipe using the read() function and prints the data that was read to 
the console using the printf() function.*/


int main(void)          // Main function of the program
{
    int pfds[2];        // Integer array of size 2 to store file descriptors
    char buf[30];       // Character array of size 30 to store data

    // Create a pipe and check if it was successful
    if (pipe(pfds) == -1) {
        perror("pipe"); // If pipe creation fails, print error message
        exit(1);        // Exit program with a non-zero status code
    }

    // Print message indicating that data will be written to write end of pipe
    printf("writing to file descriptor #%d\n", pfds[1]);

    // Write data to write end of pipe
    write(pfds[1], "test", 5);

    // Print message indicating that data will be read from read end of pipe
    printf("reading from file descriptor #%d\n", pfds[0]);

    // Read data from read end of pipe
    read(pfds[0], buf, 5);

    // Print data that was read from the pipe
    printf("read \"%s\"\n", buf);

    return 0;   // Exit program with a status code of 0 to indicate success
}
