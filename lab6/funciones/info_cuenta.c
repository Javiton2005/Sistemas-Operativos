#include "funciones.h"
#include <stdio.h>

int InfoCuenta(USER *usuario){
  
  if(usuario==NULL){
      return 4;
  }
  if (strcmp(usuario->nombre, "\0")==0){
      return 6;
  }
  if (usuario->saldo<=-1)
  {
      return 2;
  }  
  
  printf("Nombre: %s\n", usuario->nombre);
  printf("Contraseña: %s\n", usuario->contrasena);
  printf("Numero de cuenta: %s\n", usuario->ncuenta);
  printf("Saldo: %d\n", usuario->saldo);
  printf("Numero de Trasacciones: %d\n",usuario->ntrasacciones);
  
  printf("\nPresiona cualquier tecla para salir\n"); 
  getchar();
  return 0;
}
