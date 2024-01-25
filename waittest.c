#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(void)
{
    pid_t   pid;
    pid_t   res;
    int     status;

    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        usleep(500000);
        printf("Child 1 : I'm the first child !\n");
        return (54);
    }
    else if (pid > 0)
    {
		printf("%d\n", pid);
        pid = fork();
        if (pid == -1)
            return (1);
        else if(pid == 0)
        {
            usleep(499000);
            printf("Child 2 : I'm the second child...\n");
            return (10);
        }
        else if(pid > 0)
        {
            printf("Parent : I have two children !\n");
            res = wait(&status);
            printf("Parent : I received my child %d\n", res);
            if (WIFEXITED(status))
                printf("Parent : It exited successfully, exit code %d\n", WEXITSTATUS(status));
            else
                printf("Parent : It was interrupted...  is 0 ??  %d \n", WEXITSTATUS(status));
            res = wait(&status);
            printf("Parent : I received my child %d\n", res);
            if (WIFEXITED(status))
                printf("Parent : It exited successfully, exit code %d\n", WEXITSTATUS(status));
            else
                printf("Parent : It was interrupted...is 0 ??  %d \n", WEXITSTATUS(status));
        }
    }
    return (0);
}