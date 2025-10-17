#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>

#define SHM_NAME "/shared_data"

int main()
{
    pid_t pid1, pid2;

    // Start Process 1
    pid1 = fork();
    if (pid1 == 0)
    {
        execl("./process1", "process1", NULL);
        perror("Error executing process1");
        exit(1);
    }

    sleep(1); // give process1 time to create shared memory and initialize semaphores

    // Start Process 2
    pid2 = fork();
    if (pid2 == 0)
    {
        execl("./process2", "process2", NULL);
        perror("Error executing process2");
        exit(1);
    }

    // Wait for both
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    // Cleanup shared memory
    shm_unlink(SHM_NAME);

    printf("Both processes have finished.\n");
    return 0;
}
