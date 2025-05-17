#include "comun.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *EditarCsv(USER *usuario) {
   
  if (usuario == NULL) {
      perror("Error al pasar el usuario");
      exit(EXIT_FAILURE);
  }

  FILE *csv = fopen(Config.archivo_cuentas, "rb"); // Modo lectura
  if (!csv) {
      perror("Error al abrir el archivo original");
      exit(EXIT_FAILURE);
  }

  FILE *temp = fopen("temp.csv", "wb"); // Archivo temporal
  if (!temp) {
      perror("Error al crear el archivo temporal");
      fclose(csv);
      exit(EXIT_FAILURE);
  }

  printf("Nombre user: %.2lf\n",usuario->saldo); 
  char buffer[255];
  int contador = 0;

  while (fgets(buffer, sizeof(buffer), csv)) {
      if (contador == usuario->id) {
          // Reemplazar la línea del usuario
          fprintf(temp, "%s;%s;%s;%.2lf\n", usuario->nombre, usuario->contrasena, usuario->ncuenta, usuario->saldo);
      } else {
          // Copiar la línea original al archivo temporal
          fprintf(temp, "%s", buffer);
      }
      contador+=1;
  }
  fclose(csv);
  fclose(temp);

  // Reemplazar el archivo original con el nuevo archivo modificado
  remove(Config.archivo_cuentas);
  rename("temp.csv", Config.archivo_cuentas);
  return NULL;
}
