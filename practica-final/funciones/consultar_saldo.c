#include "funciones.h"
#include <stdio.h>

void ConsultarSaldo(int *idUser){

  if(idUser==NULL){
    perror("Error al pasar el id");
    exit(-1);
  }

  system("clear"); 
  printf("Saldo de la cuenta:\n");
  printf("El saldo de la cuenta de %s\n",tabla->usuarios[*idUser - 1].nombre);
  printf("Saldo: %.2lf\n", tabla->usuarios[*idUser - 1].saldo);
  printf("\nPresiona cualquier tecla para salir");
  while (getchar()!='\n'){}
  
  getchar();
  return;
}
