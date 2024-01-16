#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av, char **env)
{
    pid_t pid;

    printf("Fork here.\n");
    pid = fork();
    if (pid == -1)
    {
        // If fork returns -1, there was an error!
        return (1);
    }
    printf("\nFork successful!\n");
    if (pid == 0)
    {
        // Fork's return value is 0:
        // we are now in the child process
        printf("Child: I'm the child, my internal pid is %d.\n", pid);
    }
    else if (pid > 0)
    {
        // Fork's return value is not 0
        // which means we are in the parent process
        printf("Parent: I'm the parent, my child's pid is %d.\n", pid);
    }
	printf("\e[33mI am your father mwahahaha!\e[0m");
    return(0);
}