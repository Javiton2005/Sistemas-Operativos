#include "funciones.h"
#include <stdio.h>

void *InfoCuenta(void *usuario){
  
  if(usuario==NULL){
      return (void *)4;
  }
  USER *user = (USER *)usuario;
  if (strcmp(user->nombre, "\0")==0)
  {
      return (void *)6;
  }
  if (user->saldo<=-1)
  {
      return (void *)2;
  }    
  
  printf("Nombre: %s\n", user->nombre);
  printf("Contraseña: %s\n", user->contrasena);
  printf("Numero de cuenta: %s\n", user->ncuenta);
  printf("Saldo: %d\n", user->saldo);
  printf("Numero de Trasacciones: %d\n",user->ntrasacciones);
  
  printf("\nPresiona cualquier tecla para salir\n"); 
  getchar();
  return 0;
}
