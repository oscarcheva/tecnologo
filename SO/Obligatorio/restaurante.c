#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>

#define CAPACIDAD_MESADA 27
#define CAPACIDAD_NEVERA 25

typedef struct
{
    int platos_mesada;
    int postres_nevera;
} DatosCompartidos;

int shm_fd;
DatosCompartidos *datos;
sem_t *mutex_mesada, *mutex_nevera;
sem_t *mesada_vacia, *mesada_llena, *postres_disponibles;

void limpiar(int senal)
{
    printf("Limpiando memoria compartida y semáforos...\n");

    munmap(datos, sizeof(DatosCompartidos));
    close(shm_fd);
    shm_unlink("/cantina_shm");

    sem_close(mutex_mesada);
    sem_close(mutex_nevera);
    sem_close(mesada_vacia);
    sem_close(mesada_llena);
    sem_close(postres_disponibles);

    sem_unlink("/m_counter");
    sem_unlink("/m_fridge");
    sem_unlink("/counter_empty_slots");
    sem_unlink("/counter_full_slots");
    sem_unlink("/fridge_has_desserts");

    exit(0);
}

int main()
{
    signal(SIGINT, limpiar); // Ctrl+C activa limpieza

    // Eliminar IPC antiguos si existen
    shm_unlink("/cantina_shm");
    sem_unlink("/m_counter");
    sem_unlink("/m_fridge");
    sem_unlink("/counter_empty_slots");
    sem_unlink("/counter_full_slots");
    sem_unlink("/fridge_has_desserts");

    // Crear memoria compartida
    shm_fd = shm_open("/cantina_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(DatosCompartidos));
    datos = mmap(NULL, sizeof(DatosCompartidos), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    datos->platos_mesada = 20;  // albóndigas iniciales
    datos->postres_nevera = 18; // postres iniciales

    // Crear semáforos
    mutex_mesada = sem_open("/m_counter", O_CREAT, 0644, 1);
    mutex_nevera = sem_open("/m_fridge", O_CREAT, 0644, 1);
    mesada_vacia = sem_open("/counter_empty_slots", O_CREAT, 0644, CAPACIDAD_MESADA - datos->platos_mesada);
    mesada_llena = sem_open("/counter_full_slots", O_CREAT, 0644, datos->platos_mesada);
    postres_disponibles = sem_open("/fridge_has_desserts", O_CREAT, 0644, datos->postres_nevera);

    printf("Cantina inicializada.\n");
    printf("Comenzando con %d albóndigas y %d postres.\n", datos->platos_mesada, datos->postres_nevera);
    printf("Presione Ctrl+C para salir y limpiar recursos.\n");

    while (1)
        sleep(1); // mantener proceso vivo

    return 0;
}
