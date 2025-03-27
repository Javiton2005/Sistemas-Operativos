#include "comun.h"
#include <stdio.h>

void *EditarCsv(void *usuario){
  
  if (usuario==NULL) {
    perror("Error al pasar el usuario");
    exit(-1);
  }
  
  USER *user=(USER*) usuario;
  
  FILE *csv=fopen(Config.archivo_cuentas,"rwb");
  char buffer[255];
  int contador;
  while (fgets(buffer, sizeof(buffer), csv)) {
    contador++;
    if (contador == user->linea) {
      char linea[255];
      snprintf(linea, sizeof(linea), "%s ",user->nombre);
      fprintf(csv,); 
    }
  }

  return NULL;
}
