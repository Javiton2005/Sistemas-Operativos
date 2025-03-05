#include <stdio.h> 

#include <pthread.h> 

#include <semaphore.h> 

#include <unistd.h> 

 

// Declaración de tres semáforos binarios 

sem_t sem_A, sem_B, sem_C; 

 

// Número de iteraciones 

#define ITERACIONES 5 

 

void* hilo_A(void* arg) { 

    for (int i = 0; i < ITERACIONES; i++) { 

        sem_wait(&sem_A); // Espera su turno 

        printf("A"); 

        fflush(stdout);   // Fuerza la salida inmediata 

        sem_post(&sem_B); // Pasa el turno a B 

    } 

    return NULL; 

} 

 

void* hilo_B(void* arg) { 

    for (int i = 0; i < ITERACIONES; i++) { 

        sem_wait(&sem_B); // Espera a que A termine 

        printf("B"); 

        fflush(stdout); 

        sem_post(&sem_C); // Pasa el turno a C 

    } 

    return NULL; 

} 

 

void* hilo_C(void* arg) { 

    for (int i = 0; i < ITERACIONES; i++) { 

        sem_wait(&sem_C); // Espera a que B termine 

        printf("C"); 

        fflush(stdout); 

        sem_post(&sem_A); // Pasa el turno de vuelta a A 

    } 

    return NULL; 

} 

 

int main() { 

    pthread_t hilo1, hilo2, hilo3; 

 

    // Inicializar semáforos 

    // A inicia en 1 (puede empezar), B y C en 0 (esperan) 

    if (sem_init(&sem_A, 0, 1) == -1 ||  

        sem_init(&sem_B, 0, 1) == -1 ||  

        sem_init(&sem_C, 0, 1) == -1) { 

        perror("Error al inicializar semáforos"); 

        return 1; 

    } 

 

    // Crear los hilos 

    pthread_create(&hilo1, NULL, hilo_A, NULL); 

    pthread_create(&hilo2, NULL, hilo_B, NULL); 

    pthread_create(&hilo3, NULL, hilo_C, NULL); 

 

    // Esperar a que los hilos terminen 

    pthread_join(hilo1, NULL); 

    pthread_join(hilo2, NULL); 

    pthread_join(hilo3, NULL); 

 

    // Destruir semáforos 

    sem_destroy(&sem_A); 

    sem_destroy(&sem_B); 

    sem_destroy(&sem_C); 

 

    printf("\nPrograma terminado.\n"); 

    return 0; 
} 
