#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_TRABAJADORES 4
#define NUM_HERRAMIENTAS 6
#define ITERACIONES 3

// Semáforo no binario para herramientas
sem_t herramientas_disponibles;
// Mutex para proteger mensajes y conteo de productos
pthread_mutex_t mutex_log;
int productos_ensamblados = 0;

void* trabajador(void* arg) {
  int id = *((int*)arg);

  for (int i = 0; i < ITERACIONES; i++) {
    // Fase 1: Preparar materiales (sin herramientas)
    pthread_mutex_lock(&mutex_log);
    printf("Trabajador %d: Preparando materiales (iteración %d)...\n", id, i + 1);
    pthread_mutex_unlock(&mutex_log);
    sleep(rand() % 2); // Simula preparación

    // Fase 2: Ensamblar (necesita 2 herramientas)
    pthread_mutex_lock(&mutex_log);
    printf("Trabajador %d: Intentando ensamblar, esperando 2 herramientas...\n", id);
    pthread_mutex_unlock(&mutex_log);

    sem_wait(&herramientas_disponibles); // Toma 1ª herramienta
    sem_wait(&herramientas_disponibles); // Toma 2ª herramienta

    pthread_mutex_lock(&mutex_log);
    printf("Trabajador %d: Ensamblando producto con 2 herramientas...\n", id);
    productos_ensamblados++;
    pthread_mutex_unlock(&mutex_log);

    sleep(rand() % 2); // Simula ensamblaje

    // Libera 1 herramienta (pasa a inspección)
    sem_post(&herramientas_disponibles);

    // Fase 3: Inspeccionar (necesita 1 herramienta)
    pthread_mutex_lock(&mutex_log);
    printf("Trabajador %d: Inspeccionando producto con 1 herramienta...\n", id);
    pthread_mutex_unlock(&mutex_log);

    sleep(rand() % 2); // Simula inspección

    // Libera la última herramienta
    sem_post(&herramientas_disponibles);

    pthread_mutex_lock(&mutex_log);
    printf("Trabajador %d: Terminé iteración %d, herramientas liberadas.\n", id, i + 1);
    pthread_mutex_unlock(&mutex_log);
  }
  return NULL;
}

int main() {
  pthread_t trabajadores[NUM_TRABAJADORES];
  int ids[NUM_TRABAJADORES];

  // Inicializar semáforo y mutex
  if (sem_init(&herramientas_disponibles, 0, NUM_HERRAMIENTAS) == -1) {
    perror("Error al inicializar semáforo");
    return 1;
  }
  if (pthread_mutex_init(&mutex_log, NULL) != 0) {
    perror("Error al inicializar mutex");
    return 1;
  }

  // Crear hilos para los trabajadores
  for (int i = 0; i < NUM_TRABAJADORES; i++) {
    ids[i] = i;
    pthread_create(&trabajadores[i], NULL, trabajador, &ids[i]);
  }

  // Esperar a que los trabajadores terminen
  for (int i = 0; i < NUM_TRABAJADORES; i++) {
    pthread_join(trabajadores[i], NULL);
  }

  // Resultado final
  printf("\nProducción terminada. Total de productos ensamblados: %d\n", productos_ensamblados);

  // Destruir semáforo y mutex
  sem_destroy(&herramientas_disponibles);
  pthread_mutex_destroy(&mutex_log);

  return 0;
}

