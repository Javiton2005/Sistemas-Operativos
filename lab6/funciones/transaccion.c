#include "funciones.h"

void *TransaccionHilo(void *valor){
  IdValor *parametros = (IdValor*)valor;
  //SEM==========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  //Modificar info usuario=======================
  USER *user = leerCsv((parametros[0].id));
  USER *usero = leerCsv((parametros[1].id));
  user->saldo = user->saldo - (*(float*)(parametros->valor));
  usero->saldo = usero->saldo + (*(float*)(parametros->valor));
  //Registrar transaccion========================
  TRANSACCION transaccion;
  time_t t;
  transaccion.cantidad = (*(float*)(parametros->valor));
  transaccion.ncuentas = user->ncuenta;
  transaccion.ncuentao = usero->ncuenta;
  char *d = malloc(26);
  d = "Transaccion entre cuentas\0";
  time(&t);
  transaccion.fecha = localtime(&t);
  EscribirLogTrans(transaccion);
  EditarCsv(user);
  EditarCsv(usero);
  sem_post(semaforo);
  //FIN SEM======================================
  free(parametros);
  return(NULL);
}

void Transaccion(int *idUser){
  char nc[255];
  float c;
  pthread_t h;
  //Introduccion de datos========================
  printf("Nº de cuenta al que se le quiera hacer la transacción: \n");
  scanf("%s", nc);
  printf("¿Que cantidad quiere transferir? \n");
  scanf("%f", &c);
  //Comprobacion inicial=========================
  if (c < 0){
    printf("Formato incorrecto\n");
    return;
  }
  if (c > Config.limite_transferencia){
    printf("Cantidad excede el limite establecido en este banco\n");
  }
  //Preparacion del hilo=========================
  IdValor *parametros;
  IdValor parametro0 = {idUser, &c};
  parametros[0]=parametro0;
  //SEM==========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  USER *usero = LeerCSVNcuenta(nc); //User objetivo
  sem_post(semaforo);
  //FIN SEM======================================
  IdValor parametro1 = {&usero->id, &c};
  parametros[1]=parametro1;
  pthread_create(&h , NULL , TransaccionHilo , parametros);
  return;
}

