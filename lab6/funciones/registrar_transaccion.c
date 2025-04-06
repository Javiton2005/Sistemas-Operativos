#include "funciones.h"

void RegistrarTransaccion(TRANSACCION *transaccion) {
  char fecha[30];
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

  FILE *archivo = fopen(Config.archivo_tranferencias, "a");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return;
  }

  fprintf(archivo, "%lf;%s;%s;%s\n", transaccion->cantidad, transaccion->ncuentas, transaccion->ncuentao, fecha);
  fclose(archivo);
  return;
}