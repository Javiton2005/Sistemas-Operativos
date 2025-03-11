#include "usuarios.h"
#include <stdio.h>

USER **CrearListaUsuarios(char *fichero){

  if (fichero==NULL) {
    printf("No se a dado un fichero\n");
  }
  USER **listaUsurarios=NULL;
  char *linea=NULL;
  FILE *archivo=fopen(fichero, "r");
  char caracter;
  int caracteres=0, maxLinea=0;
  
  while ((caracter = fgetc(archivo)) != '\n' && caracter != EOF);
  

  while ((caracter=fgetc(archivo))!=EOF) {
    linea=realloc(linea, caracteres+1);

    linea[caracteres]=caracter;
    caracteres++;
    
    if (caracter=='\n') {
      linea[caracteres]='\0';
      printf("%s", linea);
      
      USER *usuario = crearUsuario(linea);
      listaUsurarios=realloc(listaUsurarios, (Estadisticas.usuarios+1)*sizeof(USER *));
      listaUsurarios[Estadisticas.usuarios-1]=usuario;
      
      caracteres=0;
    }
  }
  free(linea);
  
  for (int i = 0; i < Estadisticas.usuarios; i++) {
    char *nombre = listaUsurarios[i]->ncuenta;
    printf("Nombre: %s\n", nombre);
  }
  fclose(archivo);
  /*while (fgets(linea, 255, archivo)) {
    printf("%s\n", linea); 
  }*/

  return listaUsurarios;
}
