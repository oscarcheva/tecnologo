#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define SHM_NAME "/shm_example"
#define SEM_NAME "/sem_example"

int main()
{

    /* ------------------------------
       1. CREATE SHARED MEMORY
       ------------------------------ */
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1)
    {
        perror("shm_open");
        exit(1);
    }

    // make space for one integer
    if (ftruncate(fd, sizeof(int)) == -1)
    {
        perror("ftruncate");
        exit(1);
    }

    int *num = mmap(NULL, sizeof(int),
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED, fd, 0);

    if (num == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    // initialize value (only the first time)
    *num = 0;

    /* ------------------------------
       2. CREATE SEMAPHORE (binary)
       ------------------------------ */
    sem_t *mutex = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (mutex == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }

    /* ------------------------------
       3. USE sem_wait + sem_post
          (CRITICAL SECTION)
       ------------------------------ */
    sem_wait(mutex); // lock
    (*num)++;        // critical section
    printf("Value = %d\n", *num);
    sem_post(mutex); // unlock

    /* ------------------------------
       4. CLEANUP (optional)
       ------------------------------ */
    munmap(num, sizeof(int));
    close(fd);
    sem_close(mutex);

    // To completely delete:
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME);

    return 0;
}
