#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd[2];
    int pid;

    // check if a named pipe with the given name already exists, if not create one
    if (mkfifo("mypipe", 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    // create two file descriptors, one for reading and one for writing to the pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // fork the current process to create a child process
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // child process
        
        // close the write end of the pipe as the child only reads from it
        close(fd[1]);

        // duplicate the read end of the pipe to stdin
        dup2(fd[0], STDIN_FILENO);

        // execute the 'wc' command with the '-l' option to count the number of lines
        execlp("wc", "wc", "-l", NULL);

        // if execlp returns, there was an error
        perror("execlp");
        exit(1);
    } else {
        // parent process
        
        // close the read end of the pipe as the parent only writes to it
        close(fd[0]);

        // duplicate the write end of the pipe to stdout
        dup2(fd[1], STDOUT_FILENO);

        // execute the 'ls' command to list the files in the current directory
        execlp("ls", "ls", NULL);

        // if execlp returns, there was an error
        perror("execlp");
        exit(1);
    }

    return 0;
}
