#include "comun/comun.h"
#include "funciones/funciones.h"
#include <stdio.h>

TABLA_USUARIOS *tabla;

int main(int argc, char *argv[]){
  int idUser=atoi(argv[1]);
  int memid = atoi(argv[2]);
  tabla = (TABLA_USUARIOS*)shmat(memid, NULL, 0);
  if (tabla == NULL) {
    perror("Error al mapear la memoria compartida");
    exit(EXIT_FAILURE);
  }
  printf("Usuario %d\n", tabla->usuarios[idUser].id);
  printf("Dale a una tecla para continuar\n");
  getchar();
  while (getchar()!='\n'){}
  InitGlobal(); 
  while (1) {  
    MenuOpciones(&idUser);
  }
}
