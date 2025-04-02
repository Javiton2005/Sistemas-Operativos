#include "funciones.h"
#include <stdio.h>

void *_HiloSacarDinero(void *valor){
  if(valor==NULL){
    printf("No se ha pasado un id\n");
    exit(-1);
  }

  IdValor *parametros= (IdValor *)valor;
  
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);

  USER *user=leerCsv(parametros->id);
  if(user->saldo<(*(float*)(parametros->valor)))
    return NULL;
  user->saldo-=(*(float*)(parametros->valor));
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
  IdValor parametros = {idUser,&cantidad}; 

  pthread_create (&h1 , NULL , _HiloSacarDinero , &parametros ); 
}
