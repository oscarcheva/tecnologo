#include <stdio.h>
#include <unistd.h>

int main()
{
    int p;
    for (int i = 0; i < 3; i++)
    {
        p = fork();

        if (p == 0)
        {
            printf("Proceso hijo Nro: %d\n", i);
            printf("PID: %d\n", getpid());
            printf("PPID: %d\n", getppid());
            return 0;
        }
    }

}