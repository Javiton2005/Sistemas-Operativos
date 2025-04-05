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
    snprintf(mensaje, sizeof(mensaje),"%s %s NULL %lf %s\n", fecha, trans->ncuentas, trans->cantidad, trans->descripcion);
  }

  //SEM==========================================
  sem_t *semaforo = sem_open("/sem_log_trans", O_CREAT, 0644, 1);
  sem_wait(semaforo);

  FILE *log_trans = fopen(Config.archivo_log_transferencias,"a");
  if (!log_trans) {
    sem_post(semaforo);
    sem_close(semaforo);
    free(trans->descripcion);
    free(trans->ncuentas);
    if (trans->ncuentao) free(trans->ncuentao);
    free(trans);
    return;
  }

  fputs(mensaje, log_trans);
  fclose(log_trans);

  sem_post(semaforo);
  sem_close(semaforo);
  //FIN SEM======================================
  // Liberar memoria
  free(trans->descripcion);
  free(trans->ncuentas);
  if (trans->ncuentao) free(trans->ncuentao);
  free(trans);
}
