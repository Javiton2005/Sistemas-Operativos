#include "funciones.h"

void PagarTasas(int *idUser){
  int nc;
  char *ruta;
  char *s;
  float c;
  pthread_t h;
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
  fclose(ruta);
  if (c < 0){
    printf("Formato incorrecto\n");
    return(2);
  }
  if (c > Config.limite_transferencia){
    printf("Cantidad excede el limite establecido en este banco\n");
    return(3);
  }
  IdValor *parametros = {idUser, &c};
  pthread_create(&h , NULL , PagarTasasHilo , &parametros ); 
}

void PagarTasasHilo(void *valor){
  IdValor *parametros = (IdValor*)valor;
  printf("Iniciando pago de tasa\n");
  //SEM ================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  USER *user=leerCsv(parametros->id);
  user->saldo = user->saldo - (*(float*)(parametros->valor));
  TRANSACCION transaccion;
  time_t t;
  transaccion.cantidad = (*(float*)(parametros->valor));
  transaccion.ncuentas = user->ncuenta;
  transaccion.ncuentao = NULL;
  time(&t);
  transaccion.fecha = localtime(&t);
  transaccion.descripcion = "Pago de tasa";
  EscribirLogTrans(transaccion);
  EditarCsv(user);
  sem_post(semaforo);
  //FIN SEM ============================
  printf("Pago de tasa completado\n");
  return(0);
}
