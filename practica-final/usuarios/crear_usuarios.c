/*


  Recibe la Linea del fichero
  Devuelve un puntero a un usuario
  
  Llama a la funcion strsep con la linea y el separador

*/

#include "usuarios.h"
#include <stdio.h>


USER *crearUsuario(char *linea, int id){

  USER *user=malloc(sizeof(USER)); // Aloca memoria para un nuevo usuario
  
  int indice = 0;
  char *output;
  while((output=strsep(&linea, ";"))!= NULL){ // LLama a la funcion que devuelve una palabra

    char *palabra = strdup(output); // Duplica el valor de output una variable palabra
    if(*palabra == '\0') // Si la palabra es null o 0 lo sustituye por un N/A
      palabra = "N/A";
    switch (indice) { // Guarda el valor en la estructura de user
      case 0:
        user->nombre = palabra;
        break;
      case 1:
        user->contrasena=palabra;
        break;
      case 2:
        user->ncuenta = palabra;
        break;
      case 3:
        user->saldo = atoi(palabra);
        break;
    }
    indice++;
  }
  user->id=id;

  char path[50];
  snprintf(path, sizeof(path), "./transacciones/%s", user->ncuenta);
  mkdir(path, 0600); // Crea el directorio para las transacciones del usuario
  // 0600 permisos de lectura y escritura solo para el propietario
  // 0[propietario][grupo usuario][otros usuarios]

  return user;
}
