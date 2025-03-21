#include "usuarios.h"
#include <stdio.h>

USER **CrearListaUsuarios(char *fichero){

  if (fichero==NULL) {
    printf("No se a dado un fichero\n");
  }
  USER **listaUsuarios=NULL;
  char *linea=NULL;
  FILE *archivo=fopen(fichero, "r");
  char caracter;
  int usuarios=0;
  int caracteres=0, maxLinea=0;
  
  while ((caracter = fgetc(archivo)) != '\n' && caracter != EOF);
  

  while ((caracter=fgetc(archivo))!=EOF) {
    linea=realloc(linea, caracteres+1);

    linea[caracteres]=caracter;
    caracteres++;
    
    if (caracter=='\n') {
      linea[caracteres]='\0'; 
      USER *usuario = crearUsuario(linea);
      listaUsuarios=realloc(listaUsuarios, (usuarios)*sizeof(USER *));
      listaUsuarios[usuarios]=usuario;
      usuarios++;
      
      caracteres=0;
    }
  }
  free(linea);
  fclose(archivo);
  Estadisticas.usuarios=usuarios;
  return listaUsuarios;
}
