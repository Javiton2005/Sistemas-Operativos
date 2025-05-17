#include "comun/comun.h"
#include "funciones/funciones.h"
#include "usuarios/usuarios.h"
#include <complex.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

TABLA_USUARIOS *tabla;

int main(int argc, char *argv[]){
  InitGlobal(); 
  int idUser=atoi(argv[1]);
  int memid = atoi(argv[2]);
  pthread_t hiloGuardarDatos;
  tabla = (TABLA_USUARIOS*)shmat(memid, NULL, 0);
  if (tabla == (void *)-1) {
    perror("Error al mapear la memoria compartida");
    exit(EXIT_FAILURE);
  }


  int *bucle=malloc(sizeof(int));
  IdValor *parametros=malloc(sizeof(IdValor));
  
  *bucle=1;
  parametros->id=&idUser;
  parametros->valor=bucle;
  
  HiloArgs *args = malloc(sizeof(HiloArgs));
  args->parametros = parametros;
  args->tabla = tabla;

  pthread_create(&hiloGuardarDatos, NULL, EscribirEnLogHilo, args);

  while (1) {  
    MenuOpciones(parametros);
  }
  
  free(bucle);
  free(parametros);
  shmdt(tabla);  // desmontar memoria compartida
  pthread_join(hiloGuardarDatos, NULL);
}
