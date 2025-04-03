#include "funciones.h"

void MeterDineroHilo(void *valor){
  IdValor *parametros = (IdValor*)valor;
  //SEM==========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  //Modificar info usuario=======================
  USER *user = leerCsv(*(parametros->id));
  user->saldo = user->saldo + (*(float*)(parametros->valor));
  //Registrar transaccion========================
  TRANSACCION transaccion;
  time_t t;
  transaccion.cantidad = (*(float*)(parametros->valor));
  transaccion.ncuentas = user->ncuenta;
  transaccion.ncuentao = NULL;
  time(&t);
  transaccion.fecha = localtime(&t);
  transaccion.descripcion = "Ingreso manual\0";
  EscribirEnLogTrans(transaccion);
  EditarCsv(user);
  //FIN SEM======================================
  sem_post(semaforo);
  return(0);
}

void MeterDinero(int *idUser){
  float c;
  pthread_t h;
  //Introduccion de datos========================
  printf("Cantidad a ingresar: \n");
  scanf("%f", &c);
  //Comprobacion inicial=========================
  if (c > 0){
    printf("Formato incorrecto\n");
    return;
  }
  if (c > Config.limite_transferencia){
    printf("Cantidad excede el limite establecido en este banco\n");
    return;
  }
  //Preparacion del hilo=========================
  IdValor parametros = {idUser, &c};
  pthread_create(&h , NULL , MeterDineroHilo , &parametros);
  return;
}