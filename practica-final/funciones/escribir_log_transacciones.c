#include "funciones.h"
#include <semaphore.h>
#include <stdio.h>
#include <time.h>

void EscribirLogTrans(TRANSACCION *trans){
  char fecha[30], mensaje[100];
  time_t t;
  struct tm *tm_info;
  t = time(NULL); 
  tm_info=localtime(&t);
  // Coje la fecha de la transaccion
  strftime(fecha, sizeof(fecha), "%d-%m-%Y %H:%M:%S", tm_info);
  if(trans->ncuentao)
    snprintf(mensaje, sizeof(mensaje),"%s %s %s %.2lf %s\n", fecha, trans->ncuentas, trans->ncuentao, trans->cantidad, trans->descripcion);
  else{
    snprintf(mensaje, sizeof(mensaje),"%s %s NULL %.2lf %s\n", fecha, trans->ncuentas, trans->cantidad, trans->descripcion);
  }

  //SEM==========================================
  sem_t *semaforo = sem_open("/sem_log_trans", O_CREAT, 0644, 1);
  sem_wait(semaforo);

  // Crea el directorio de transacciones
  char PathCuentaSalida[20];
  snprintf(PathCuentaSalida, sizeof(PathCuentaSalida), "./transacciones/%s/transacciones.log", trans->ncuentas);

  // Abre o crea y abre archivo log para guardar transaccion salida
  FILE *log_trans = fopen(PathCuentaSalida,"a");

  // En caso de fallo se resetean semaforos y se libera memoria
  if (!log_trans) {
    sem_post(semaforo);
    sem_close(semaforo);
    free(trans->ncuentas);
    if (trans->ncuentao) free(trans->ncuentao);
    free(trans);
    return;
  }

  FILE *log_trans2 = NULL;

  // Si la transaccion tiene como objetivo a otro usuario, crea el log de la cuenta objetivo y escribe en el
  if (trans->ncuentao != NULL) {
    char PathCuentaObjetivo[20];
    snprintf(PathCuentaObjetivo, sizeof(PathCuentaObjetivo), "./transacciones/%s/transacciones.log", trans->ncuentao);

    // Abre o crea y abre archivo log para guardar transaccion objetivo
    FILE *log_trans2 = fopen(PathCuentaObjetivo,"a");

    // En caso de fallo se resetean semaforos y se libera memoria
    if (!log_trans2) {
      sem_post(semaforo);
      sem_close(semaforo);
      free(trans->ncuentas);
      if (trans->ncuentao) free(trans->ncuentao);
      free(trans);
      return;
    }
  }

  fputs(mensaje, log_trans);
  fclose(log_trans);

  if (trans->ncuentao != NULL)
  {
    fputs(mensaje, log_trans2);
    fclose(log_trans2);
  }
  
  sem_post(semaforo);
  sem_close(semaforo);
  //FIN SEM======================================
  // Liberar memoria
  free(trans->ncuentas);
  if (trans->ncuentao) free(trans->ncuentao);
  free(trans);
}
