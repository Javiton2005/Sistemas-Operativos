#include "funciones.h"
#include <semaphore.h>
#include <stdio.h>

void *_HiloSacarDinero(void *valor){
  if(valor==NULL){
    printf("No se ha pasado un id\n");
    exit(-1);
  }

  IdValor *parametros= (IdValor *)valor;
  
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  sem_wait(semaforo);
  USER *user=leerCsv(parametros->id);

  
  if(user->saldo<(*(double*) (parametros->valor))){
    sem_post(semaforo);
    return NULL;
  }

  user->saldo-=(*(double*)(parametros->valor));
  /*TRANSACCION transaccion;*/
  /*time_t t;*/
  /*transaccion.cantidad = (*(double*)(parametros->valor));*/
  /*transaccion.ncuentas = user->ncuenta;*/
  /*transaccion.ncuentao = NULL;*/
  /*time(&t);*/
  /*transaccion.fecha = localtime(&t);*/
  /*transaccion.descripcion = "Retirada manual";*/
  /*EscribirLogTrans(transaccion);*/
  EditarCsv(user);

  sem_post(semaforo);
  return NULL;
}


void SacarDinero(int *idUser){
  
  pthread_t h1 ;
  double cantidad;

  system("clear");
  printf("Introduce la cantidad a sacar:");
  scanf("%lf",&cantidad);
  if(cantidad<0){
    perror("No se pueden introducir numeros negativos");
    return;
  }
  IdValor parametros = {idUser,(void *)&cantidad}; 

  pthread_create (&h1 , NULL , _HiloSacarDinero , &parametros );
}
