#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

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
            int fd = open("archivo.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);
            switch (i)
            {
            case 0:
            {
                execlp("ls", "ls", "/etc", NULL);
                perror("execlp failed");
                exit(1);
            }
            case 1:
            {
                execlp("ps", "ps", "-ef", NULL);
                perror("execlp failed");
                exit(1);
            }
            case 2:
            {
                execlp("netstat", "netstat", "-npr", NULL);
                perror("execlp failed");
                exit(1);
            }
            }
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

    execlp("cat", "cat", "archivo.txt", NULL);
    perror("execlp failed");
    return 1;
}