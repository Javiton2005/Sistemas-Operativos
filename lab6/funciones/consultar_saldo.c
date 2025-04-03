#include "funciones.h"
#include <stdio.h>

void ConsultarSaldo(int *idUser){

  if(idUser==NULL){
    perror("Error al pasar el id");
    exit(-1);
  }
  USER *user = leerCsv(idUser);

  system("clear"); 
  printf("Saldo de la cuenta:\n");
  printf("El saldo de la cuenta de %s\n",user->nombre);
  printf("Saldo: %f\n", user->saldo);
  printf("\nPresiona cualquier tecla para salir");
  while (getchar()!='\n'){}
  
  getchar();
  return;
}
