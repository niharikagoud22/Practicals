#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        /* Child process */
        printf("Child Process: PID = %d\n", getpid());
        printf("Child: Exiting immediately...\n");

        exit(0);
    }
    else
    {
        /* Parent process */
        printf("Parent Process: PID = %d\n", getpid());
        printf("Parent: Child PID = %d\n", pid);

        printf("\nParent: Not calling wait() immediately.\n");
        printf("Parent: Child will become a zombie process.\n");
        printf("Parent: Sleeping for 20 seconds...\n");

        sleep(20);

        /* Reap the zombie process */
        wait(&status);

        printf("\nParent: Child process reaped.\n");
        printf("Parent: Zombie process eliminated.\n");
    }

    return 0;
}
