#include "funciones.h"

void *CancelarTarjetaHilo(void *valor){
  IdValor *parametros = (IdValor*)valor;
  //SEM =========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  //Modificar info usuario=======================
  USER *user = leerCsv(parametros->id);
  user->ncuenta = (parametros->valor);
  EditarCsv(user);
  sem_post(semaforo);
  sem_close(semaforo);
  //FIN SEM =====================================
  free(parametros->valor);
  free(parametros);
  free(user);
  return(NULL);
}

void CancelarTarjeta(int *idUser){
  char *n = malloc(255);
  pthread_t h;
  //Introduccion de datos========================
  printf("Ingrese el nuevo numero de cuenta que quiera tener(9 caracteres): \n");
  scanf("%s",n);
  //Comprobacion inicial=========================
  if ((strlen(n) != 9) || (atoi(n)<=0)){
    printf("Formato incorrecto\n");
    return;
  }
  //Preparacion del hilo=========================
  IdValor parametros = {idUser, n};
  pthread_create(&h , NULL , CancelarTarjetaHilo , &parametros);
}
