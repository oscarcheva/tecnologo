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
    sem_t *sem;

    srand(time(NULL));

    sem = sem_open("/sem.txt", O_CREAT, 0666, 0);
    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    ptr = setup_shared_memory(SHM_NAME, SHM_SIZE);

    *ptr = 10; // Optional: remove if Restador initializes first
    printf("Sumador - Esperando que el restador inicie\n");
    sem_wait(sem); // wait until Restador posts

    for (i = 0; i < CANT; i++)
    {
        a = *ptr;
        printf("Sumador lee: %d\n", a);
        a++;
        for (j = 0; j < rand() % TOPE; j++)
            ; // small delay
        *ptr = a;
        printf("Sumador graba: %d\n", a);
    }

    printf("Fin Sumador: %d\n", *ptr);

    sem_post(sem); // signal finished
    sem_close(sem);

    shm_unlink(SHM_NAME);
    sem_unlink("/sem.txt");

    return 0;
}
