#include "funciones.h"

void *PagarTasasHilo(void *valor){
  IdValor *parametros = (IdValor*)valor;
  //SEM =========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  //Modificar info usuario=======================
  USER *user=leerCsv(parametros->id);
  user->saldo = user->saldo - (*(double*)(parametros->valor));
  //Registrar transaccion========================
  TRANSACCION transaccion;
  time_t t;
  transaccion.cantidad = (*(double*)(parametros->valor));
  transaccion.ncuentas = user->ncuenta;
  transaccion.ncuentao = NULL;
  time(&t);
  transaccion.fecha = localtime(&t);
  transaccion.descripcion = "Pago de tasa";
  EscribirLogTrans(transaccion);
  EditarCsv(user);
  sem_post(semaforo);
  //FIN SEM =====================================
  return(NULL);
}

void PagarTasas(int *idUser){
  int nc;
  char *ruta;
  char *s;
  double c;
  pthread_t h;
  ruta = malloc(256);
  s = malloc(256);
  FILE *tasa;
  //Introduccion de datos========================
  printf("Ruta del archivo de la tasa: \n");
  scanf("%s", ruta);
  //Comprobacion inicial=========================
  if ((tasa = fopen(ruta, "rb"))==NULL){
    printf("Fichero de tasa no existe\n");
    return;
  }
  fgets(s, 256, tasa);
  fclose(tasa);
  c = atof(s);
  free(ruta);
  free(s);
  if (c < 0){
    printf("Formato incorrecto\n");
    return;
  }
  if (c > Config.limite_transferencia){
    printf("Cantidad excede el limite establecido en este banco\n");
    return;
  }
  //Preparacion del hilo=========================
  IdValor parametros = {idUser, (void *)&c};
  pthread_create(&h , NULL , PagarTasasHilo , &parametros); 
}