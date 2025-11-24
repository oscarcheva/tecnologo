#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define BANDEJA_ALBONDIGAS 4
#define BANDEJA_POSTRES 6

typedef struct
{
    int platos_mesada;
    int postres_nevera;
} DatosCompartidos;

DatosCompartidos *datos;
sem_t *mutex_mesada, *mesada_llena, *mesada_vacia;
sem_t *mutex_nevera, *postres_disponibles;

void *servir_albondigas(void *arg)
{
    while (1)
    {
        int disponibles, a_tomar = BANDEJA_ALBONDIGAS;
        sem_getvalue(mesada_llena, &disponibles);
        if (disponibles < BANDEJA_ALBONDIGAS)
            a_tomar = disponibles;

        if (a_tomar > 0)
        {
            for (int i = 0; i < a_tomar; i++)
                sem_wait(mesada_llena);

            sem_wait(mutex_mesada);
            datos->platos_mesada -= a_tomar;
            printf("[Mozos] Tomó %d platos de albóndigas. Mesada: %d\n", a_tomar, datos->platos_mesada);
            sem_post(mutex_mesada);

            for (int i = 0; i < a_tomar; i++)
                sem_post(mesada_vacia);
        }

        usleep(300000 + rand() % 2700000); // 0.3s a 3s
    }
    return NULL;
}

void *servir_postres(void *arg)
{
    while (1)
    {
        int disponibles, a_tomar = BANDEJA_POSTRES;
        sem_getvalue(postres_disponibles, &disponibles);
        if (disponibles < BANDEJA_POSTRES)
            a_tomar = disponibles;

        if (a_tomar > 0)
        {
            for (int i = 0; i < a_tomar; i++)
                sem_wait(postres_disponibles);

            sem_wait(mutex_nevera);
            datos->postres_nevera -= a_tomar;
            printf("[Mozos] Tomó %d postres. Nevera: %d\n", a_tomar, datos->postres_nevera);
            sem_post(mutex_nevera);
        }

        usleep(300000 + rand() % 2700000); // 0.3s a 3s
    }
    return NULL;
}

int main()
{
    srand(time(NULL));

    // Abrir memoria compartida
    int shm_fd = shm_open("/cantina_shm", O_RDWR, 0666);
    datos = mmap(NULL, sizeof(DatosCompartidos), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Abrir semáforos
    mutex_mesada = sem_open("/m_counter", 0);
    mesada_llena = sem_open("/counter_full_slots", 0);
    mesada_vacia = sem_open("/counter_empty_slots", 0);

    mutex_nevera = sem_open("/m_fridge", 0);
    postres_disponibles = sem_open("/fridge_has_desserts", 0);

    printf("Mozos (camareros) iniciados...\n");

    pthread_t hilo_albondigas, hilo_postres;
    pthread_create(&hilo_albondigas, NULL, servir_albondigas, NULL);
    pthread_create(&hilo_postres, NULL, servir_postres, NULL);

    pthread_join(hilo_albondigas, NULL);
    pthread_join(hilo_postres, NULL);

    return 0;
}
