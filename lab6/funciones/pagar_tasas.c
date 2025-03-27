#include "funciones.h"

int PagarTasas(){
  int nc;
  char *ruta;
  char *s;
  float c;
  ruta = malloc(256);
  s = malloc(256);
  FILE *tasa;
  printf("Ruta del archivo de la tasa: \n");
  scanf("%s", ruta);
  if ((tasa = fopen(ruta, "r"))==NULL){
    printf("Fichero de tasa no existe\n");
    return(1);
  }
  fgets(s, 256, tasa);
  sscanf(s, "%f", &c);
  fgets(s, 256, tasa);
  if (c < 0){
    printf("Formato incorrecto\n");
    return(2);
  }
  if (c > MAX_TRANSACCION){
    printf("Cantidad excede el limite establecido en este banco\n");
    return(3);
  }
  printf("Iniciando pago de tasa\n");
  user->saldo = user->saldo - c;
  TRANSACCION transaccion;
  time_t t;
  transaccion.cantidad = c;
  transaccion.ncuentas = user->ncuenta;
  transaccion.ncuentao = NULL;
  time(&t);
  transaccion.fecha = localtime(&t);
  transaccion.descripcion = s;
  ModificarCSV(user);
  printf("Pago de tasa completado\n");
  return(0);
}