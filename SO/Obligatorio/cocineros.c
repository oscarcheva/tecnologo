#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define CAPACIDAD_MESADA 27
#define CAPACIDAD_NEVERA 25

typedef struct
{
    int platos_mesada;
    int postres_nevera;
} DatosCompartidos;

int main()
{
    // Inicializar semilla para números aleatorios
    srand(time(NULL));

    // Abrir memoria compartida
    int fd = shm_open("/cantina_shm", O_RDWR, 0666);
    DatosCompartidos *datos = mmap(NULL, sizeof(DatosCompartidos),
                                   PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Abrir semáforos con nombre
    sem_t *mutex_mesada = sem_open("/m_counter", 0);
    sem_t *mutex_nevera = sem_open("/m_fridge", 0);
    sem_t *mesada_vacia = sem_open("/counter_empty_slots", 0);
    sem_t *mesada_llena = sem_open("/counter_full_slots", 0);
    sem_t *postres_disponibles = sem_open("/fridge_has_desserts", 0);

    printf("Cocineros iniciados...\n");

    pid_t pid = fork();
    if (pid == 0)
    {
        // Hijo: cocinero de albóndigas
        while (1)
        {
            int tiempo_coccion = 300000 + rand() % 500000; // 0.3s a 1s
            usleep(tiempo_coccion);

            sem_wait(mesada_vacia);

            sem_wait(mutex_mesada);
            datos->platos_mesada++;
            printf("[Cocinero] Preparó albóndiga. Mesada: %d\n", datos->platos_mesada);
            sem_post(mutex_mesada);

            sem_post(mesada_llena);
        }
    }
    else
    {
        // Padre: cocinero de postres
        while (1)
        {
            sem_wait(mutex_nevera);

            if (datos->postres_nevera == 0)
            {
                printf("[Cocinero Postres] Nevera vacía! Reponiendo a %d\n", CAPACIDAD_NEVERA);
                for (int i = 0; i < CAPACIDAD_NEVERA; i++)
                    sem_post(postres_disponibles);
                datos->postres_nevera = CAPACIDAD_NEVERA;
            }

            sem_post(mutex_nevera);
            usleep(300000); // simular preparación de postres
        }
    }

    while (1)
        sleep(1);

    return 0;
}
