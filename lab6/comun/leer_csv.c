#include "comun.h" 
#include "../usuarios/usuarios.h"
#include <stdio.h>

USER *leerCsv(int *idLinea){
  USER *usuario;

  if (idLinea<0) {
    perror("Introduce un id Valido de usuario 0-n");
    return NULL;
  }
  if (strlen(Config.archivo_cuentas)<1) {
    perror("Introduce un fichero de cuentas valido");
  }
  FILE *fichero = fopen(Config.archivo_cuentas, "rb");
  char linea[255];
  for (int i =0;i<=*idLinea;i++) {
    fgets(linea, sizeof(linea), fichero);
  }

  usuario=crearUsuario(linea,*idLinea);

  if(usuario!=NULL)
    return usuario;
  else{
    perror("Error al crear usuario");
    return NULL;
  }
}
