#include "usuarios.h"

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
      listaUsuarios=realloc(listaUsuarios, (Estadisticas.usuarios)*sizeof(USER *));
      listaUsuarios[Estadisticas.usuarios]=usuario;
      Estadisticas.usuarios++;
      
      caracteres=0;
    }
  }
  free(linea);
  fclose(archivo);
  
  return listaUsuarios;
}
