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

void CrearListaUsuarios(TABLA_USUARIOS *tabla, char *fichero) {
  if (fichero == NULL) { // Si no pasan fichero retorna un error
    printf("No se ha dado un fichero\n");
    return;
  }

  if (tabla == NULL) { // Verifica que la memoria compartida ya esté asignada
    printf("Error: la memoria compartida no está inicializada\n");
    exit(-1);
  }

  char *linea = NULL;
  FILE *archivo = fopen(fichero, "rb"); // Abre el fichero
  if (!archivo) {
    printf("Error al abrir el archivo de cuentas.\n");
    exit(-1);
  }

  char caracter;
  int usuarios = 0;
  int caracteres = 0;

  while ((caracter = fgetc(archivo)) != '\n' && caracter != EOF); // Se salta la primera línea

  while (1) {
    caracter = fgetc(archivo); // Lee el fichero carácter por carácter

    if (caracter == EOF) break;
    linea = realloc(linea, caracteres + 1); // Realoca memoria para la línea

    linea[caracteres] = caracter; // Añade el carácter a la línea
    caracteres++;

    if (caracter == '\n' || caracter == EOF) {
      linea[caracteres] = '\0';
      crearUsuario(linea, usuarios + 1, &tabla->usuarios[usuarios]); // Crea el usuario directamente en la memoria compartida
      usuarios++;
      caracteres = 0;
    }
  }

  free(linea);
  fclose(archivo);
  tabla->num_usuarios = usuarios; // Actualiza el número de usuarios en la tabla
}