#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>

#define SHM_NAME "/shml"
#define SHM_SIZE 4096

// --- Shared memory setup function ---
int *setup_shared_memory(const char *name, int size)
{
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, size) == -1)
    {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    int *ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    close(shm_fd); // no longer needed after mmap
    return ptr;
}

// --- Main program ---
int main()
{
    const int TOPE = 90000000;
    const int CANT = 10;

    int i, a, j;
    int *ptr;
    sem_t *semS;
    sem_t *semR;

    srand(time(NULL));

    semS = sem_open("/semS", O_CREAT, 0666, 0); // initially 0
    if (semS == SEM_FAILED)
    {
        perror("sem_open semS");
        exit(1);
    }

    semR = sem_open("/semR", O_CREAT, 0666, 0); // initially 0
    if (semR == SEM_FAILED)
    {
        perror("sem_open semR");
        exit(1);
    }

    ptr = setup_shared_memory(SHM_NAME, SHM_SIZE);

    *ptr = 10; // Optional: remove if Restador initializes first
    printf("Sumador - Esperando que el restador inicie\n");

    for (i = 0; i < CANT; i++)
    {
        sem_wait(semS); // wait until Restador posts
        a = *ptr;
        printf("Sumador lee: %d\n", a);
        a++;
        *ptr = a;
        printf("Sumador graba: %d\n", a);
        sem_post(semR);
    }

    printf("Fin Sumador: %d\n", *ptr);

    sem_post(semS); // signal finished
    sem_close(semS);

    sem_unlink("/semS");
    sem_unlink("/semR");

    return 0;
}
