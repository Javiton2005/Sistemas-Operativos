#include "funciones.h"
#include <stdio.h>

void *MeterDineroHilo(void *valor){
  if(valor==NULL){
    printf("No se ha pasado un id\n");
    exit(-1);
  }
  IdValor *parametros = (IdValor *)valor;
  //SEM==========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  sem_wait(semaforo);
  //Modificar info usuario=======================
  USER *user = leerCsv(parametros->id);

  user->saldo +=(*(double*)(parametros->valor));
  //Registrar transaccion========================
  /*TRANSACCION transaccion;*/
  /*time_t t;*/
  /*transaccion.cantidad = (*(double*)(parametros->valor));*/
  /*transaccion.ncuentas = user->ncuenta;*/
  /*transaccion.ncuentao = NULL;*/
  /*time(&t);*/
  /*transaccion.fecha = localtime(&t);*/
  /*transaccion.descripcion = "Ingreso manual\0";*/
  /*EscribirLogTrans(transaccion);*/

  EditarCsv(user);
  
  //FIN SEM======================================
  sem_post(semaforo);
  sem_close(semaforo);
  return(NULL);
}

void MeterDinero(int *idUser){
  
  double *cantidad = malloc(sizeof(double));

  if (!cantidad) {
    perror("malloc falló");
    return;
  }
  pthread_t h;
  
  system("clear");

  //Introduccion de datos========================
  printf("Introduce la cantidad a ingresar: ");
  scanf("%lf", cantidad);
  //Comprobacion inicial=========================
  if (cantidad < 0){
    printf("Formato incorrecto\n");
    return;
  }
 if (*cantidad > Config.limite_transferencia){
    printf("Cantidad excede el limite establecido en este banco\n");
    return;
  }
  IdValor *parametros = malloc(sizeof(IdValor));
  if (!parametros) {
    perror("malloc falló");
    return;
  }
  parametros->id = idUser;
  parametros->valor = cantidad;

  pthread_create(&h , NULL , MeterDineroHilo , parametros);
}
