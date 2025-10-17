#include <sys/mman.h>  // mmap, PROT_*, MAP_*
#include <sys/stat.h>  // mode constants
#include <fcntl.h>     // O_* constants (for shm_open)
#include <unistd.h>    // close, ftruncate
#include <stdlib.h>    // exit, EXIT_FAILURE, etc.
#include <stdio.h>     // printf, perror
#include <semaphore.h> // sem_t and semaphore functions
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
    *ptr = 10;

    printf("Restador - Iniciando todo\n");
    sem_post(sem);

    for (i = 0; i < CANT; i++)
    {
        a = *ptr;
        printf("Restador lee: %d\n", a);
        a--;
        for (j = 0; j < rand() % TOPE; j++)
            ; // delay
        *ptr = a;
        printf("Restador graba: %d\n", a);
    }

    printf("Fin Restador: %d\n", *ptr);

    sem_post(sem);
    sem_close(sem);
    sem_unlink("/sem.txt");
    shm_unlink(SHM_NAME);

    return 0;
}
