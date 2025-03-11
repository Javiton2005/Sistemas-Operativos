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
  int caracteres=0, maxLinea=0;
  
  while ((caracter = fgetc(archivo)) != '\n' && caracter != EOF);
  

  while ((caracter=fgetc(archivo))!=EOF) {
    linea=realloc(linea, caracteres+1);

    linea[caracteres]=caracter;
    caracteres++;
    
    if (caracter=='\n') {
      linea[caracteres]='\0'; 
      USER *usuario = crearUsuario(linea);
      listaUsuarios=realloc(listaUsuarios, (Estadisticas.usuarios+1)*sizeof(USER *));
      listaUsuarios[Estadisticas.usuarios-1]=usuario;
      
      caracteres=0;
    }
  }
  free(linea);
  
  fclose(archivo);
  /*while (fgets(linea, 255, archivo)) {
    printf("%s\n", linea); 
  }*/

  return listaUsuarios;
}
