#include "funciones.h"
#include <semaphore.h>
#include <stdio.h>

void *TransaccionHilo(void *valor){
  IdValor *parametros = (IdValor*)valor;
  char mensaje[256];
  //SEM==========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);

  //printf("ID 2:%d",*parametros[1].id);
  //Modificar info usuario=======================
  USER *user = leerCsv((parametros[0].id));
  USER *usero = leerCsv((parametros[1].id));
  if(user->saldo<(*(double*) (parametros->valor))){
    sem_post(semaforo);
    sem_close(semaforo);
    // Crea el mensaje del para escribir en el log
    snprintf(mensaje, sizeof(mensaje),"[Warning] Intento de transferencia superior a la cantidad User id: %d",user->id);
    EscribirEnLog(mensaje);
    return NULL;
  }
  user->saldo = user->saldo - (*(double*)(parametros->valor));
  usero->saldo = usero->saldo + (*(double*)(parametros->valor));
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
  transaccion->ncuentas = strdup(user->ncuenta);
  transaccion->ncuentao = strdup(usero->ncuenta);
  transaccion->descripcion = "Transferencia entre cuentas";
  EscribirLogTrans(transaccion);
  EditarCsv(user);
  EditarCsv(usero);
  sem_post(semaforo);
  sem_close(semaforo);
  //FIN SEM======================================
  notificar_hilos();
  snprintf(mensaje, sizeof(mensaje),"Transferencia de dinero realizado por el User: %d de cantidad %.2lf al User: %d",user->id, *(double*)(parametros->valor),usero->id);
  EscribirEnLog(mensaje);
  free(parametros);
  free(usero);
  free(user);
  return(NULL);
}

void Transaccion(int *idUser){
  char nc[255];
  double *c = malloc(sizeof(double));
  pthread_t h;
  int *idUsero;
  system("clear");
  //Introduccion de datos========================
  printf("Nº de cuenta al que se le quiera hacer la transacción: ");
  scanf("%s", nc);
  printf("¿Que cantidad quiere transferir? ");
  scanf("%lf", c);
  //Comprobacion inicial=========================
  if (c < 0){
    printf("Formato incorrecto\n");
    sleep(2);
    return;
  }
  if (*c > Config.limite_transferencia){
    printf("Cantidad excede el limite establecido en este banco\n");
    sleep(2);
    return;
  }
  //Preparacion del hilo=========================
  IdValor *parametros = malloc(2 * sizeof(IdValor)); // Allocate memory for 2 IdValor structs
  if (!parametros) {
    printf("Error al asignar memoria para parametros\n");
    sleep(2);
    return;
  }
  parametros[0].valor=c;
  parametros[0].id=idUser;

  idUsero = LeerCSVNcuenta(nc); //User objetivo
  if(*idUsero==-1){
    perror("No se a encontrado al usuario\n");
    printf("Presiona enter para salir\n");
    while (getchar()!='\n');
    getchar();
    return;
  }

  parametros[1].id=idUsero;
  parametros[1].valor=c;
  pthread_create(&h , NULL , TransaccionHilo , parametros);
  return;
}

