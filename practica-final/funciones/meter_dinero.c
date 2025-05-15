#include "funciones.h"
#include <stdio.h>

void *MeterDineroHilo(void *valor){
  if(valor==NULL){
    printf("No se ha pasado un id\n");
    exit(-1);
  }
  IdValor *parametros = (IdValor *)valor;
  char mensaje[256];
  //SEM==========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  sem_wait(semaforo);
  //Modificar info usuario=======================
  tabla->usuarios[*(parametros->id) - 1].saldo += *(double*)(parametros->valor);
  //Registrar transaccion========================
  TRANSACCION *transaccion=malloc(sizeof(TRANSACCION));
  if(!transaccion){
    sem_post(semaforo);
    sem_close(semaforo);
    free(parametros->valor); // Libera el double
    free(parametros);        // Libera el struct
    exit(-1);
  }

  transaccion->cantidad = (*(double*)(parametros->valor));
  transaccion->ncuentas = strdup(tabla->usuarios[*(parametros->id) - 1].ncuenta);
  transaccion->ncuentao = NULL;
  transaccion->descripcion = "Ingreso manual";
  RegistrarTransaccion(transaccion);
  EscribirLogTrans(transaccion);
  
  sem_post(semaforo);
  sem_close(semaforo);
  //FIN SEM======================================

  snprintf(mensaje, sizeof(mensaje),"Ingreso de dinero realizado por el User: %d de cantidad %.2lf", tabla->usuarios[*(parametros->id) - 1].id, *(double*)(parametros->valor));
  free(parametros->valor); // Libera el double
  free(parametros);  
  
  EscribirEnLog(mensaje);
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
