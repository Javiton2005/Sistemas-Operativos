#include "funciones.h"

void *PagarTasasHilo(void *valor){
  char mensaje[256];
  IdValor *parametros = (IdValor*)valor;
  //SEM =========================================
  sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
  sem_wait(semaforo);
  //Modificar info usuario=======================
  USER *user=leerCsv(parametros->id);
  user->saldo -= (*(double*)(parametros->valor));
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
  transaccion->descripcion = "Pago de tasas";
  RegistrarTransaccion(transaccion);
  EscribirLogTrans(transaccion);
  //============================================
  EditarCsv(user);
  sem_post(semaforo);
  sem_close(semaforo);
  snprintf(mensaje, sizeof(mensaje),"Pago de tasa realizado por el User: %d de cantidad %.2lf",user->id, *(double*)(parametros->valor));
  EscribirEnLog(mensaje);
  free(user);
  free(parametros->valor); // Libera el double
  free(parametros);        // Libera el struct
  //FIN SEM =====================================
  notificar_hilos(); // Llamada a monitor para verificar anomalías

  return(NULL);
}

void PagarTasas(int *idUser){
  int nc;
  char ruta[255];
  char *s;
  double *c = malloc(sizeof(double));
  pthread_t h;
  s = malloc(256);
  FILE *tasa;
  //Introduccion de datos========================
  system("clear");
  printf("Ruta del archivo de la tasa: \n");
  scanf("%s", ruta);
  //Comprobacion inicial=========================
  if ((tasa = fopen(ruta, "rb"))==NULL){
    printf("Fichero de tasa no existe\n");
    sleep(2);
    free(s);
    return;
  }
  s[strcspn(s, "\n")] = 0; // Eliminar el salto de línea
  fgets(s, 256, tasa);
  fclose(tasa);
  *c = atoi(s);
  free(s);
  if (*c < 0){
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
  IdValor *parametros = malloc(sizeof(IdValor));
  if (!parametros) {
    perror("malloc falló");
    return;
  }
  parametros->id = idUser;
  parametros->valor = c;
  pthread_create(&h , NULL , PagarTasasHilo , parametros); 
  return;
}
