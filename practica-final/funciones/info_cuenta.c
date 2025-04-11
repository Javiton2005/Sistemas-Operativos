#include "funciones.h"
#include <stdio.h>

void InfoCuenta(int *idUser){
  
  if (idUser<0) {
    return;
  }
  int memid = shm_open(Config.clave, O_CREAT | O_RDWR, 0666);
  USER **usuario = (USER **)mmap(NULL, sizeof(USER) * Estadisticas.usuarios, PROT_READ | PROT_WRITE, MAP_SHARED, memid, 0);
  USER *user;
  for (int i = 0; i < Estadisticas.usuarios; i++) {
    if (usuario[i]->id == *idUser) {
      user = usuario[i];
      break;
    }
  }

  system("clear");
  printf("Info de la cuenta:\n"); 
  printf("Nombre: %s\n", user->nombre);
  printf("Contraseña: %s\n", user->contrasena);
  printf("Numero de cuenta: %s\n", user->ncuenta);
  printf("Saldo: %.2lf\n", user->saldo);
  printf("Id: %d",user->id);
  printf("\nPresiona cualquier tecla para salir"); 
  while (getchar() != '\n'); // Limpiamos el buffer de entrada
  getchar();
  return;
}
