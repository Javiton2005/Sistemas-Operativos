#include "funciones.h"

void CancelarTarjetaHilo(void *valor){
  IdValor *parametros = (IdValor*)valor;
  //SEM =========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  //Modificar info usuario=======================
  USER *user = leerCsv(parametros->id);
  user->ncuenta = (parametros->valor);
  EditarCsv(user);
  sem_post(semaforo);
  //FIN SEM =====================================
  return;
}

void CancelarTarjeta(int *idUser){
  char *n;
  pthread_t h;
  //Introduccion de datos========================
  printf("Ingrese el nuevo numero de cuenta quiera tener: \n");
  scanf("%s",n);
  //Comprobacion inicial=========================
  if(!atoi(n)) return;
  //Preparacion del hilo=========================
  IdValor parametros = {idUser, &n};
  pthread_create(&h , NULL , CancelarTarjetaHilo , &parametros);
  return;
}