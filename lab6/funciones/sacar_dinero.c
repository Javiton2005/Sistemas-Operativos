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

  USER *user=leerCsv(parametros->id);
  if(user->saldo<(*(float*) parametros->valor)){
    sem_post(semaforo);
    return NULL;
  }
  user->saldo-=(*(float*)(parametros->valor));
  /*TRANSACCION transaccion;*/
  /*time_t t;*/
  /*transaccion.cantidad = (*(float*)(parametros->valor));*/
  /*transaccion.ncuentas = user->ncuenta;*/
  /*transaccion.ncuentao = NULL;*/
  /*time(&t);*/
  /*transaccion.fecha = localtime(&t);*/
  /*transaccion.descripcion = "Retirada manual";*/
  /*EscribirLogTrans(transaccion);*/
  EditarCsv(user); 

  sem_post(semaforo);
  getchar();
  return NULL;
}


void SacarDinero(int *idUser){
  
  pthread_t h1 ;
  float cantidad;

  system("clear");
  printf("Introduce la cantidad a sacar:");
  scanf("%f",&cantidad);
  IdValor parametros = {idUser,&cantidad}; 

  pthread_create (&h1 , NULL , _HiloSacarDinero , &parametros );
  pthread_join(h1,NULL);
}
