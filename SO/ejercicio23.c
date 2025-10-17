#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    int p;
    printf("Proceso abuelo \n");
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    fflush(stdout);

    p = fork();
    if (p == 0)
    {
        printf("Proceso padre\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        fflush(stdout);

        p = fork();
        if (p == 0)
        {
            printf("Proceso nieto/hijo\n");
            printf("PID: %d\n", getpid());
            printf("PPID: %d\n", getppid());
            fflush(stdout);
            return 0;a
        }
        wait(NULL);
        return 0;
    }
    wait(NULL);
    return 0;
}