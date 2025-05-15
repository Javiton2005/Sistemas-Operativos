#include "funciones.h"

void RegistrarTransaccion(TRANSACCION *transaccion,int idUser) {
  char fecha[30];
  char nombre_archivo[50];
  time_t t;
  struct tm *tm_info;
  t = time(NULL); 
  tm_info=localtime(&t);
  // Coje la fecha de la transaccion
  strftime(fecha, sizeof(fecha), "%d-%m-%Y %H:%M:%S", tm_info);
  if (transaccion == NULL) {
    fprintf(stderr, "Error: transaccion es NULL\n");
    return;
  }
  sprintf(nombre_archivo, "./ficheros/%d/transacciones.log", 1000 + idUser);
  FILE *archivo  = fopen(nombre_archivo, "a");
  if(archivo==NULL){
    printf("No se ha podido abrir el fichero %s\n",nombre_archivo);
  }

  fprintf(archivo, "%.2lf;%s;%s;%s\n", transaccion->cantidad, transaccion->ncuentas, transaccion->ncuentao, fecha);
  fclose(archivo);
  return;
}
