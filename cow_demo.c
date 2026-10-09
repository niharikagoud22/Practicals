#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE (100 * 1024 * 1024)

int main(void)
{
    char *memory = malloc(SIZE);

    if (memory == NULL)
    {
        perror("malloc");
        return 1;
    }

    printf("Allocated 100 MB memory\n");
    printf("Parent PID: %d\n", getpid());

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        free(memory);
        return 1;
    }

    if (pid == 0)
    {
        printf("Child PID: %d\n", getpid());
        printf("Child modifying memory...\n");

        for (size_t i = 0; i < SIZE; i += 4096)
        {
            memory[i] = 1;
        }

        printf("Child modification completed.\n");

        free(memory);
        return 0;
    }
    else
    {
        printf("Child PID: %d\n", pid);
        printf("Parent waiting for child...\n");

        wait(NULL);

        printf("Child finished.\n");

        free(memory);
    }

    return 0;
}
