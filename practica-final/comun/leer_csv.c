#include "comun.h" 
#include "../usuarios/usuarios.h"
#include <stdio.h>

USER *leerCsv(int *idLinea){
  USER *usuario=malloc(sizeof(USER));
  if(usuario==NULL){
    exit(-1);
  }

  if (*idLinea<0) {
    perror("Introduce un id Valido de usuario 0-n");
    return NULL;
  }
  if (strlen(Config.archivo_cuentas)<1) {
    perror("Introduce un fichero de cuentas valido");
    return NULL;
  }
  FILE *fichero = fopen(Config.archivo_cuentas, "rb");

  if (!fichero) {
    perror("No se pudo abrir el archivo de cuentas");
    return NULL;
  }
  char linea[255];

  for (int i = 0; i <= *idLinea; i++) {
    if (!fgets(linea, sizeof(linea), fichero)) {
        perror("ID de usuario fuera de rango");
        fclose(fichero);
        free(usuario);
        return NULL;
    }
  }
  crearUsuario(linea,*idLinea,usuario);
  fclose(fichero);
  if(usuario!=NULL)
    return usuario;
  else{
    perror("Error al crear usuario");
    return NULL;
  }
}
