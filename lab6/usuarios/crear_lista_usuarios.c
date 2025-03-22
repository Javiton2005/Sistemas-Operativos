/*
 * Recibe una direccion de un fichero .csv
 * El archivo lo abre y lo lee linea a linea 
 * mandando la linea a la funcion crear usuario
 * La funcion retorna un puntero a un usuario
 * y lo añade a una lista de usuarios que es la que retorna
 *
 *
*/



#include "usuarios.h"
#include <stdio.h>

USER **CrearListaUsuarios(char *fichero){
  if (fichero==NULL) { // Si no pasan fichero retorna null y un error;
    printf("No se a dado un fichero\n");
    return(NULL);
  }
  USER **listaUsuarios=NULL; // Lista de usuarios que se retornara
  char *linea=NULL;
  FILE *archivo=fopen(fichero, "r"); // Abre el fichero
  char caracter;
  int usuarios=0;
  int caracteres=0;
  
  while ((caracter = fgetc(archivo)) != '\n' && caracter != EOF); // Se salta la primera linea
  

  while (1) {
    caracter=fgetc(archivo); // lee el fichero hasta el final carcater por caracter
    linea=realloc(linea, caracteres+1); // Realoca memoria para la linea para añadir el caracter

    linea[caracteres]=caracter; // Añade el caracter en la posicion indicada
    caracteres++;
    
    if (caracter=='\n' || caracter ==EOF) {
      linea[caracteres]='\0'; 
      USER *usuario = crearUsuario(linea);
      //free(linea);
      listaUsuarios=realloc(listaUsuarios, (usuarios)*sizeof(USER *));
      listaUsuarios[usuarios]=usuario;
      usuarios++;
      
      caracteres=0;
    }
    if(caracter==EOF)
      break;
  }
  free(linea);
  fclose(archivo);
  Estadisticas.usuarios=usuarios;
  return listaUsuarios;
}
