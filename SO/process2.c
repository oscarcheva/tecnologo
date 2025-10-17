#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define SHM_NAME "/shared_data"
#define SIZE sizeof(shared_data_t)

typedef struct
{
    int counter;
    sem_t sem_p1;
    sem_t sem_p2;
} shared_data_t;

int main()
{
    // Open existing shared memory
    int shm_fd;
    shared_data_t *shared;

    // Retry until shared memory is ready
    for (int i = 0; i < 10; i++)
    {
        shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
        if (shm_fd != -1)
            break;
        perror("Waiting for shared memory...");
        sleep(1);
    }
    if (shm_fd == -1)
    {
        perror("shm_open failed");
        exit(1);
    }

    shared = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    close(shm_fd);

    srand(time(NULL));

    for (int i = 0; i <= 10; i++)
    {
        sem_wait(&shared->sem_p2);

        int ms = (rand() % 401) + 100;
        shared->counter -= 1;
        printf("Process 2: %d\n", shared->counter);
        usleep(ms * 1000);

        sem_post(&shared->sem_p1);
    }

    munmap(shared, SIZE);
    return 0;
}
