#include "funciones.h"
#include <stdio.h>

void InfoCuenta(int *idUser){
  
  if (idUser<0) {
    return;
  }

  system("clear");
  printf("Info de la cuenta:\n"); 
  printf("Nombre: %s\n", tabla->usuarios[*idUser - 1].nombre);
  printf("Contraseña: %s\n", tabla->usuarios[*idUser - 1].contrasena);
  printf("Numero de cuenta: %s\n", tabla->usuarios[*idUser - 1].ncuenta);
  printf("Saldo: %.2lf\n", tabla->usuarios[*idUser - 1].saldo);
  printf("Id: %d",*idUser);
  printf("\nPresiona cualquier tecla para salir"); 
  while (getchar() != '\n'); // Limpiamos el buffer de entrada
  getchar();
  return;
}
