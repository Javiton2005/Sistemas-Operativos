#include "funciones.h"
#include <stdio.h>

void InfoCuenta(int *idUser){
  
  if (idUser<0) {
    return;
  }
  
  USER *user=leerCsv(idUser); 

  system("clear");
  printf("Info de la cuenta:\n"); 
  printf("Nombre: %s\n", user->nombre);
  printf("Contraseña: %s\n", user->contrasena);
  printf("Numero de cuenta: %s\n", user->ncuenta);
  printf("Saldo: %lf\n", user->saldo);
  printf("Id: %d",user->id);
  printf("\nPresiona cualquier tecla para salir"); 
  while (getchar() != '\n'); // Limpiamos el buffer de entrada
  getchar();
  return;
}
