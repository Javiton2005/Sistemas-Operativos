#include "funciones.h"
#include <semaphore.h>
#include <stdio.h>

void *_HiloSacarDinero(void *valor){
  if(valor==NULL){
    printf("No se ha pasado un id\n");
    exit(-1);
  }

  IdValor *parametros= (IdValor *)valor;
  
  char mensaje[256];
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  sem_wait(semaforo);
  USER *user=leerCsv(parametros->id);

  
  if(user->saldo<(*(double*) (parametros->valor))){
    sem_post(semaforo);
    sem_close(semaforo);

    // Crea el mensaje del para escribir en el log
    snprintf(mensaje, sizeof(mensaje),"[Warning] Intento de retiro superior a la cantidad User id: %d",user->id);
    EscribirEnLog(mensaje);
    return NULL;
  }
  user->saldo-=(*(double*)(parametros->valor));
  
  TRANSACCION *transaccion=malloc(sizeof(TRANSACCION));
  if(!transaccion){
    sem_post(semaforo);
    sem_close(semaforo);
    free(parametros->valor); // Libera el double
    free(parametros);        // Libera el struct
    exit(-1);
  }
  transaccion->cantidad = (*(double*)(parametros->valor));
  transaccion->ncuentas = strdup(user->ncuenta);
  transaccion->ncuentao = NULL;
  transaccion->descripcion = "Retirada manual";
  RegistrarTransaccion(transaccion);
  EscribirLogTrans(transaccion);

  EditarCsv(user);


  sem_post(semaforo);
  sem_close(semaforo);

  notificar_hilos(); // Llamada a monitor para verificar anomalías
  
  snprintf(mensaje, sizeof(mensaje),"Retiro de dinero realizado por el User: %d de cantidad %.2lf",user->id, *(double*)(parametros->valor));
  free(parametros->valor); // Libera el double
  free(parametros);        // Libera el struct

  EscribirEnLog(mensaje);
  free(user);
  return NULL;
}


void SacarDinero(int *idUser){
  
  pthread_t h1 ;
  double *cantidad=malloc(sizeof(double));

  if (!cantidad) {
    perror("malloc falló");
    return;
  }
  system("clear");
  printf("Introduce la cantidad a sacar: ");
  scanf("%lf",cantidad);
  if(cantidad<0){
    perror("No se pueden introducir numeros negativos");
    return;
  }
  IdValor *parametros = malloc(sizeof(IdValor));
  if (!parametros) {
    perror("malloc falló");
    return;
  }
  parametros->id = idUser;
  parametros->valor = cantidad;

  pthread_create(&h1, NULL, _HiloSacarDinero, parametros);
}
