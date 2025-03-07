#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
int main() {
  sem_t *sem;
  FILE *file;
  char buffer[100];
  // Abrir el semáforo nombrado
  sem = sem_open("/mi_semaforo", O_CREAT, 0644, 1); // Valor inicial = 1
  if (sem == SEM_FAILED) {
    perror("Error al abrir el semáforo en Consumidor");
    exit(1);
  }
  for (int i = 0; i < 5; i++) {
    sem_wait(sem); // Espera el semáforo
    // Abrir el archivo compartido en modo lectura
    file = fopen("recurso_compartido.txt", "r");
    if (file == NULL) {
      perror("Error al abrir el archivo");
      sem_post(sem);
      exit(1);
    }
    // Leer la última línea (simplificado para este ejemplo)
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
      printf("Consumidor lee: %s", buffer);
    }
    fclose(file);
    sleep(1); // Simula trabajo
    sem_post(sem); // Libera el semáforo
    sleep(1); // Da tiempo al productor
  }
  // Cerrar el semáforo en este proceso
  sem_close(sem);
  // Eliminar el semáforo del sistema (solo lo hace uno de los procesos al final)
  sem_unlink("/mi_semaforo");
  return 0;
}
