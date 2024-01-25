#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    pid_t   pid;
    int     ends[2]; // The 2 ends of the pipe: (2 fds)
                     // ends[0] : read end
                     // ends[1] : write end
    char    secret[30];
    int     reader;
    char    buffer[30];

    // Create a pipe and error check
    if (pipe(ends) == -1)
        return (1);
    // Create a child process
    pid = fork();
    if (pid == -1)
        return (1);
    else if (pid == 0)
    {
        // Child process
        close(ends[0]); // Nothing we want to read, close pipe's read end.
        printf("Child: I'm writing my secret in the pipe...\n");
        strcpy(secret, "I am your child, mwahaha!");
        write(ends[1], secret, strlen(secret));
        close(ends[1]); // Done writing, close pipe's write end.
        return (0);
    }
    else
    {
        // Parent process
        close(ends[1]); // Nothing to write, close pipe's write end.
        waitpid(pid, NULL, 0); // Wait for child.
        printf("Parent: I received my child. What is its secret ?\n");
        reader = read(ends[0], buffer, 30);
        close(ends[0]); // Read everything, close pipe's read end.
        if (reader == -1)
            return (3);
        buffer[reader] = '\0';
        printf("Parent: Oh boy! The secret is : \"%s\"\n", buffer);
    }
}