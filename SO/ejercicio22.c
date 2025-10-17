#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    int p;
    printf("Proceso padre \n");
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    fflush(stdout);

    for (int i = 0; i < 3; i++)
    {
        p = fork();

        if (p == 0)
        {
            printf("Proceso hijo Nro: %d\n", i);
            printf("PID: %d\n", getpid());
            printf("PPID: %d\n", getppid());
            fflush(stdout);

            return 0;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        wait(NULL); // block until one child ends, throw away exit status
    }

    printf("All child have finished, we are done\n");
}