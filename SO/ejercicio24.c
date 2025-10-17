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

    for (int i = 0; i <= 1; i++)
    {
        p = fork();

        if (p == 0)
        {
            printf("Proceso hijo Nro: %d\n", i + 1);
            printf("PID: %d\n", getpid());
            printf("PPID: %d\n", getppid());
            fflush(stdout);
            if (i == 1)
            {
                int q = fork();
                if (q == 0)
                {

                    printf("Proceso nieto\n");
                    printf("PID: %d\n", getpid());
                    printf("PPID: %d\n", getppid());
                    fflush(stdout);
                    return 0;
                }
                wait(NULL);
            }

            return 0;
        }
    }
    // int status;
    // for (int i = 0; i < 3; i++)
    // {
    //     p = wait(&status);
    //     if (WIFEXITED(status))
    //     {
    //         printf("Child with PID %d finished with exit code %d\n",
    //                p, WEXITSTATUS(status));
    //     }
    // }

    for (int i = 0; i < 3; i++)
    {
        wait(NULL); // block until one child ends, throw away exit status
    }

    printf("All child have finished, we are done\n");
}