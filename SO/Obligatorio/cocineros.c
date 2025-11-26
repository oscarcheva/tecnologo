#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define CAPACIDAD_NEVERA 25

typedef struct
{
    int platos_mesada;
    int postres_nevera;
} DatosCompartidos;

int main()
{
    srand(time(NULL));

    int shm_fd = shm_open("/cantina_shm", O_RDWR, 0666);
    DatosCompartidos *datos = mmap(NULL, sizeof(DatosCompartidos),
                                   PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t *mutex_mesada = sem_open("/m_counter", 0);
    sem_t *mesada_vacia = sem_open("/counter_empty_slots", 0);
    sem_t *mesada_llena = sem_open("/counter_full_slots", 0);

    sem_t *mutex_nevera = sem_open("/m_fridge", 0);
    sem_t *postres_disponibles = sem_open("/fridge_has_desserts", 0);

    printf("Cocineros iniciados...\n");

    // Spawn 3 meatball cooks
    for (int i = 0; i < 3; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            while (1)
            {
                usleep(500000 + (rand() % 1500000));

                sem_wait(mesada_vacia);
                sem_wait(mutex_mesada);

                datos->platos_mesada++;
                printf("Cocinero %d Preparó 1 albóndiga. Mesada: %d\n",
                       i + 1, datos->platos_mesada);

                sem_post(mutex_mesada);
                sem_post(mesada_llena);
            }
        }
    }

    // Spawn 1 dessert cook
    pid_t pid = fork();
    if (pid == 0)
    {
        while (1)
        {
            sem_wait(mutex_nevera);

            if (datos->postres_nevera == 0)
            {
                printf("Cocinero de Postres dice --- Nevera vacía, estoy Reponiendo %d flanes ---\n",
                       CAPACIDAD_NEVERA);

                for (int i = 0; i < CAPACIDAD_NEVERA; i++)
                    sem_post(postres_disponibles);

                datos->postres_nevera = CAPACIDAD_NEVERA;
            }

            sem_post(mutex_nevera);
        }
    }

    while (1)
        sleep(1);
    return 0;
}
