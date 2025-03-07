#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
int main() {
  sem_t *sem;
  FILE *file;
  // Abrir el semáforo nombrado (se crea si no existe)
  sem = sem_open("/mi_semaforo", O_CREAT, 0644, 1); // Valor inicial = 1
  if (sem == SEM_FAILED) {
    perror("Error al abrir el semáforo en Productor");
    exit(1);
  }
  for (int i = 0; i < 5; i++) {
    sem_wait(sem); // Espera el semáforo
    // Abrir el archivo compartido en modo append
    file = fopen("recurso_compartido.txt", "a");
    if (file == NULL) {
      perror("Error al abrir el archivo");
      sem_post(sem);
      exit(1);
    }
    fprintf(file, "Productor escribe: Mensaje %d\n", i);
    printf("Productor: Mensaje %d escrito\n", i);
    fclose(file);
    sleep(1); // Simula trabajo
    sem_post(sem); // Libera el semáforo
    sleep(1); // Da tiempo al consumidor
  }
  // Cerrar el semáforo en este proceso
  sem_close(sem);
  return 0;
}
