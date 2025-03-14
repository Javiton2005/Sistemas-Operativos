#include "usuarios.h"

USER *crearUsuario(char *linea){
  //printf("%s", linea);
  USER *user=malloc(sizeof(USER));
  
  int indice = 0;
  char *output;
  while((output=strsep(&linea, ";"))!= NULL){    

    char *palabra = strdup(output);
    if(*palabra == '\0')
      palabra = "N/A";
    //printf("%s\n", palabra); 
    switch (indice) {
      case 0:
        user->nombre = palabra;
        break;
      case 1:
        user->contrasena=palabra;
        break;
      case 2:
        user->ncuenta = palabra;
        break;
      case 3:
        user->saldo = atoi(palabra);
        break;
      case 4:
        user->ntrasacciones=atoi(palabra);
        break;
    }
    indice++;
  }
  return user;
}
