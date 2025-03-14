#include "login.h"
#include <stdio.h>

void *login(USER **listaUsuarios){

  char nombre[50];
  char contraseña[50];

  printf("\n\nEstadisticas Usuarios: %d\n\n", Estadisticas.usuarios);

  printf("Inserta Nombre de la cuenta: ");
  scanf("%s", nombre);

  printf("Inserta Contraseña de la cuenta: ");
  scanf("%s", contraseña);
  
  for(int i =0;i<Estadisticas.usuarios;i++){
    if (strcmp(nombre, listaUsuarios[i]->nombre)==0 && strcmp(contraseña, listaUsuarios[i]->contrasena)==0) {
      return listaUsuarios[i];
    }
  }
  printf("Retorna NULL");
  return NULL;
}
