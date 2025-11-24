#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define COUNTER_CAPACITY 27
#define FRIDGE_CAPACITY 25

// Shared resources
int counter_plates = 0; // meatballs
int fridge_desserts = FRIDGE_CAPACITY;

// Mutexes
pthread_mutex_t m_counter;
pthread_mutex_t m_fridge;

// Semaphores to manage available/space
sem_t counter_empty_slots;
sem_t counter_full_slots;
sem_t fridge_has_desserts;

// Initialization
void initialize_shared_resources()
{
    counter_plates = 0;
    fridge_desserts = FRIDGE_CAPACITY;

    pthread_mutex_init(&m_counter, NULL);
    pthread_mutex_init(&m_fridge, NULL);

    sem_init(&counter_empty_slots, 0, MESADA);
    sem_init(&counter_full_slots, 0, 0);
    sem_init(&fridge_has_desserts, 0, FRIDGE_CAPACITY);
}
