#include "funciones.h"
#include <stdio.h>

void *InfoCuenta(void *usuario){
  char letra;
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
  system("clear");
  printf("Info de la cuenta:\n"); 
  printf("Nombre: %s\n", user->nombre);
  printf("Contraseña: %s\n", user->contrasena);
  printf("Numero de cuenta: %s\n", user->ncuenta);
  printf("Saldo: %d\n", user->saldo);
  printf("Numero de Trasacciones: %d\n",user->ntrasacciones);
  
  printf("\nPresiona cualquier tecla para salir"); 
  while (getchar() != '\n'); // Limpiamos el buffer de entrada
  getchar();
  return 0;
}
