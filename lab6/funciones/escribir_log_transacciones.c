#include "funciones.h"

void EscribirLogTrans(TRANSACCION trans){
  char fecha[50], mensaje[100];

  // Coje la fecha de la transaccion
  strftime(fecha, sizeof(fecha), "%d-%m-%Y %H:%M:%S", trans.fecha);
  snprintf(mensaje, sizeof(mensaje),"%s %s %s %lf %s\n", fecha, trans.ncuentas, trans.ncuentao, trans.cantidad, trans.descripcion);
  //SEM==========================================
  sem_t *sem = sem_open("/sem_log_trans", O_CREAT, 0644, 1);
  FILE *log = fopen(Config.archivo_log_tranferencias,"a");
  fputs(trans.descripcion, log);
  fclose(log);
  sem_post(sem);
  //FIN SEM======================================
}
