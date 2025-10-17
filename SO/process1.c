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
    // Create or open shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(1);
    }
    ftruncate(shm_fd, SIZE);

    shared_data_t *shared = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    close(shm_fd);

    // Initialize shared data and semaphores (only first process should do this)
    shared->counter = 0;
    sem_init(&shared->sem_p1, 1, 1); // Process1 starts unlocked
    sem_init(&shared->sem_p2, 1, 0); // Process2 starts locked

    srand(time(NULL));

    for (int i = 0; i <= 10; i++)
    {
        sem_wait(&shared->sem_p1);

        int ms = (rand() % 401) + 100;
        shared->counter += 1;
        printf("Process 1: %d\n", shared->counter);
        usleep(ms * 1000);

        sem_post(&shared->sem_p2);
    }

    munmap(shared, SIZE);
    return 0;
}
