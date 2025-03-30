#include "comun.h"

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
    if (contador == user->id) {
      char linea[255];
      snprintf(linea, sizeof(linea), "%s;%s;%s;%f;%d",user->nombre,user->contrasena,user->ncuenta,user->saldo,user->ntransacciones);
      fprintf(csv,"%s",linea);
    }
  }
  return NULL;
}
