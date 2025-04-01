#include "funciones.h"

int Transaccion(int *idUser){
  char nc[255];
  float c;
  pthread_t h;
  printf("Nº de cuenta al que se le quiera hacer la transacción: \n");
  scanf("%s", &nc);
  printf("¿Que cantidad quiere transferir? \n");
  scanf("%f", &c);
  if (c < 0){
    printf("Formato incorrecto\n");
    return(4);
  }
  if (c > Config.limite_transferencia){
    printf("Cantidad excede el limite establecido en este banco\n");
  }
  IdValor *parametros;
  IdValor parametro0 = {idUser, &c};
  parametros[0]=parametro0;
  //SEM==============================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  USER *usero = leerCsvNcuenta(nc);
  sem_post(semaforo);
  //FIN SEM============================
  IdValor parametro1 = {usero->id, &c};
  parametros[1]=parametro1;
  pthread_create(&h , NULL , TransaccionHilo , parametros);
  return(NULL);
}
void TransaccionHilo(void *valor){
  IdValor *parametros = (IdValor*)valor;
  printf("Iniciando transaccion\n");
  //SEM================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  USER *user = leerCsv(*(parametros[0].id));
  USER *usero = leerCsv(*(parametros[1].id));
  user->saldo = user->saldo - *(parametros[0].valor);
  usero->saldo = usero->saldo + *(parametros[1].valor);
  TRANSACCION transaccion;
  time_t t;
  transaccion.cantidad = *(parametros[0].valor);
  transaccion.ncuentas = user->ncuenta;
  transaccion.ncuentao = usero->ncuenta;
  char *d = malloc(26);
  d = "Transaccion entre cuentas\0";
  time(&t);
  transaccion.fecha = localtime(&t);
  EscribirLogTrans(transaccion);
  ModificarCSV(user);
  ModificarCSV(usero);
  sem_post(semaforo);
  //FIN SEM==============================
  free(parametros);
  printf("Transaccion completada\n");
  return;
}
