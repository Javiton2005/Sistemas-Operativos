#include "funciones.h"
#include <stdio.h>

void ConsultarSaldo(USER *usuario){

  if (strcmp(usuario->nombre, "\0")==0)
  {
      return;
  }
  if (usuario->saldo<=-1)
  {
      return;
  }

  system("clear"); 
  printf("Saldo de la cuenta:\n");
  printf("El saldo de la cuenta de %s\n",usuario->nombre);
  printf("Saldo: %d\n", usuario->saldo);
  printf("\nPresiona cualquier tecla para salir");
  while (getchar()!='\n'){}
  
  getchar();
  return;
}
