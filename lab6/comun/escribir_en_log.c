/*
 * Es una funcion para unificar la escritura del fichero de log
 * Recibe la linea que hay qeu añadir
 *
*/

#include "comun.h"

void EscribirEnLog(char *frase){
  char mensaje[100];
  time_t t;
  struct tm *tm_info;
  char fecha[50];
  t = time(NULL); 
  
  tm_info = localtime(&t);
  // Coje la fecha del sistema
  strftime(fecha, sizeof(fecha), "%d-%m-%Y %H:%M:%S", tm_info);
  snprintf(mensaje, sizeof(mensaje),"%s %s\n", fecha, frase);
  // Bloquea el sistema por medio de semaforos
  sem_t *semaforo = sem_open("/semaforo_log", O_CREAT, 0644, 1);
  FILE *banco = fopen(Config.archivo_log,"a"); // Abre el fichero
  fputs(mensaje, banco); // Añade la linea al final del fichero
  fclose(banco);
  sem_post(semaforo);
}
