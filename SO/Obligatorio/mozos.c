// mozos_solo_threads.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>

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

/* --- Funciones de mozos (hilos) --- */

void *camarero_albondigas_hilo(void *arg)
{
    int indice = *(int *)arg;

    int a_tomar = 0;
    for (int j = 0; j < BANDEJA_ALBONDIGAS; j++)
    {
        if (sem_trywait(mesada_llena) == -1)
        {
            if (errno == EAGAIN)
                break;
            else
                break;
        }
        a_tomar++;
    }

    if (a_tomar > 0)
    {
        sem_wait(mutex_mesada);
        datos->platos_mesada -= a_tomar;
        printf("Mozo %d Tomó %d albondigas. Mesada: %d\n",
               indice, a_tomar, datos->platos_mesada);
        fflush(stdout);
        sem_post(mutex_mesada);

        for (int j = 0; j < a_tomar; j++)
            sem_post(mesada_vacia);
    }

    return NULL;
}

void *camarero_postres_hilo(void *arg)
{
    int indice = *(int *)arg; // get the 1–5 index

    int a_tomar = 0;
    for (int j = 0; j < BANDEJA_POSTRES; j++)
    {
        if (sem_trywait(postres_disponibles) == -1)
        {
            if (errno == EAGAIN)
                break;
            else
                break;
        }
        a_tomar++;
    }

    if (a_tomar > 0)
    {
        sem_wait(mutex_nevera);
        datos->postres_nevera -= a_tomar;
        printf("Mozo %d Tomó %d postres. Nevera: %d\n",
               indice, a_tomar, datos->postres_nevera);
        fflush(stdout);
        sem_post(mutex_nevera);
    }

    return NULL;
}

/* Lanzadores: crean tandas de 5 mozos y esperan a que terminen */
void *servir_albondigas(void *arg)
{
    (void)arg;
    while (1)
    {
        pthread_t hilos[5];
        int indices[5];
        for (int i = 0; i < 5; i++)
        {
            usleep(1000000 + (rand() % 2000000));

            indices[i] = i + 1;

            if (pthread_create(&hilos[i], NULL, camarero_albondigas_hilo, &indices[i]) != 0)
                perror("pthread_create albondigas");
        }
        for (int i = 0; i < 5; i++)
            pthread_join(hilos[i], NULL);
    }
    return NULL;
}

void *servir_postres(void *arg)
{
    (void)arg;
    while (1)
    {
        pthread_t hilos[5];
        int indices[5];
        for (int i = 0; i < 5; i++)
        {
            indices[i] = i + 1;

            usleep(1000000 + (rand() % 2000000));

            if (pthread_create(&hilos[i], NULL, camarero_postres_hilo, &indices[i]) != 0)
                perror("pthread_create postres");
        }
        for (int i = 0; i < 5; i++)
            pthread_join(hilos[i], NULL);
    }
    return NULL;
}

int main()
{
    /* Desactivar buffering de stdout */
    setvbuf(stdout, NULL, _IONBF, 0);
    srand(time(NULL));

    /* Abrir memoria compartida (se asume creada externamente) */
    int shm_fd = shm_open("/cantina_shm", O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open");
        return 1;
    }

    datos = mmap(NULL, sizeof(DatosCompartidos), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (datos == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }

    /* Abrir semáforos (se asume creados externamente) */
    mutex_mesada = sem_open("/m_counter", 0);
    mesada_llena = sem_open("/counter_full_slots", 0);
    mesada_vacia = sem_open("/counter_empty_slots", 0);
    mutex_nevera = sem_open("/m_fridge", 0);
    postres_disponibles = sem_open("/fridge_has_desserts", 0);

    if (mutex_mesada == SEM_FAILED || mesada_llena == SEM_FAILED || mesada_vacia == SEM_FAILED ||
        mutex_nevera == SEM_FAILED || postres_disponibles == SEM_FAILED)
    {
        perror("sem_open");
        return 1;
    }

    printf("Mozos iniciados (hilos)...\n");

    pthread_t hilo_albondigas, hilo_postres;
    if (pthread_create(&hilo_albondigas, NULL, servir_albondigas, NULL) != 0)
    {
        perror("pthread_create hilo_albondigas");
        return 1;
    }
    if (pthread_create(&hilo_postres, NULL, servir_postres, NULL) != 0)
    {
        perror("pthread_create hilo_postres");
        return 1;
    }

    pthread_join(hilo_albondigas, NULL);
    pthread_join(hilo_postres, NULL);

    return 0;
}
