#include "login.h"

void *login(USER **listaUsuarios){

  char *nombre;
  char *contraseña;
  printf("Inserta Nombre de la cuenta: ");
  scanf("%s", nombre);

  printf("Inserta Contraseña de la cuenta: ");
  scanf("%s", contraseña);
  
  for(int i =0;i<Estadisticas.usuarios;i++){
    if (strcmp(nombre, listaUsuarios[i]->nombre)==0 && strcmp(contraseña, listaUsuarios[i]->contrasena)==0) {
      printf("El usuario coincide\n");
      return listaUsuarios[i];
    }
    else {
      printf("%s %s no conicide\n", listaUsuarios[i]->nombre, listaUsuarios[i]->contrasena);
    }
  }
  printf("Retorna NULL");
  return NULL;
}




    //printf("%s no conicide\n", listaUsuarios[i]->contrasena);
    /*if (strcmp(nombre, listaUsuarios[i]->nombre)==0 && strcmp(contraseña, listaUsuarios[i]->contrasena)==0) {
      //printf("Hay cuenta\n");
      break;
    }
    else {
      //printf("%s %s no conicide\n", listaUsuarios[i]->nombre, listaUsuarios[i]->contrasena);
    }*/
