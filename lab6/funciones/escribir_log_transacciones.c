#include "funciones.h"

void EscribirLogTrans(TRANSACCION trans){
  char fecha[50], mensaje[100];

  // Coje la fecha del sistema
  strftime(fecha, sizeof(fecha), "%d-%m-%Y %H:%M:%S", trans.fecha);
  snprintf(mensaje, sizeof(mensaje),"%s %s %s %f %s\n", fecha, trans.ncuentas, trans.ncuentao, trans.cantidad, trans.descripcion);
  // Bloquea el sistema por medio de semaforos
  sem_t *sem = sem_open("/sem_log_trans", O_CREAT, 0644, 1);
  FILE *log = fopen(Config.archivo_log_tranferencias,"a"); // Abre el fichero
  fputs(trans.descripcion, log); // Añade la linea al final del fichero
  fclose(log);
  sem_post(sem);
}
