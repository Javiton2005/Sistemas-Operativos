#include "funciones.h"

void *TransaccionHilo(void *valor){
  IdValor *parametros = (IdValor*)valor;
  //SEM==========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  //Modificar info usuario=======================
  USER *user = leerCsv((parametros[0].id));
  USER *usero = leerCsv((parametros[1].id));
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
  transaccion->ncuentas = strdup(user->ncuenta); // si ya es string
  transaccion->ncuentao = NULL;
  transaccion->descripcion = strdup("Transferencia entre cuentas");
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
  double c;
  pthread_t h;
  //Introduccion de datos========================
  printf("Nº de cuenta al que se le quiera hacer la transacción: \n");
  scanf("%s", nc);
  printf("¿Que cantidad quiere transferir? \n");
  scanf("%lf", &c);
  //Comprobacion inicial=========================
  if (c < 0){
    printf("Formato incorrecto\n");
    sleep(2);
    return;
  }
  if (c > Config.limite_transferencia){
    printf("Cantidad excede el limite establecido en este banco\n");
    sleep(2);
    return;
  }
  printf("gucci pa2\n");
  //Preparacion del hilo=========================
  IdValor *parametros = malloc(2 * sizeof(IdValor)); // Allocate memory for 2 IdValor structs
  if (!parametros) {
    printf("Error al asignar memoria para parametros\n");
    return;
  }
  IdValor parametro0 = {idUser, &c};
  parametros[0] = parametro0;
  printf("gucci pa3\n");
  //SEM==========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  sem_wait(semaforo);
  USER *usero = LeerCSVNcuenta(nc); //User objetivo
  sem_post(semaforo);
  //FIN SEM======================================
  printf("gucci pa4\n");
  IdValor parametro1 = {&usero->id, &c};
  parametros[1]=parametro1;
  printf("gucci pa1\n");
  pthread_create(&h , NULL , TransaccionHilo , parametros);
  return;
}

