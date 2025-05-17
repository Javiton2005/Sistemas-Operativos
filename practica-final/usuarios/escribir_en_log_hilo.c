#include "usuarios.h"
#include <stdio.h>
#include <unistd.h>

void *EscribirEnLogHilo(void *arg){
  HiloArgs *args = (HiloArgs *)arg;
  
  IdValor *parametros = args->parametros;
  TABLA_USUARIOS *tabla = args->tabla; 
  int *bucle= (int *)(parametros->valor);
  
  sem_t *semaforo = sem_open("/sem_dbcsv_global", O_CREAT, 0644, 1);
  while (*bucle){
    if (semaforo == SEM_FAILED) {
      perror("sem_open falló");
      return NULL;
    }
    sem_wait(semaforo);  
    EditarCsv(&tabla->usuarios[*parametros->id-1]);
    sleep(30);
    sem_post(semaforo);

  }
  
  sem_close(semaforo);
  return NULL;
}
