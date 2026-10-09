#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_data = 10;

int main(void)
{
    static int static_data = 20;

    int stack_var = 30;

    int *heap_var = malloc(sizeof(int));

    if (heap_var == NULL)
    {
        perror("malloc");
        return 1;
    }

    *heap_var = 40;

    printf("Process ID: %d\n", getpid());

    printf("Global address : %p\n", (void *)&global_data);
    printf("Static address : %p\n", (void *)&static_data);
    printf("Heap address   : %p\n", (void *)heap_var);
    printf("Stack address  : %p\n", (void *)&stack_var);

    printf("\nProcess is running...\n");
    printf("Open another terminal and inspect:\n");
    printf("cat /proc/%d/maps\n", getpid());

    while (1)
    {
        sleep(10);
    }

    free(heap_var);

    return 0;
}
