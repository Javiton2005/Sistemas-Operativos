/*


  Recibe la Linea del fichero
  Devuelve un puntero a un usuario
  
  Llama a la funcion strsep con la linea y el separador

*/

#include "usuarios.h"
#include <stdio.h>


void crearUsuario(char *linea, int id, USER *user) {
  
  int indice = 0;
  char *palabra;
  while((palabra=strsep(&linea, ";"))!= NULL){ // LLama a la funcion que devuelve una palabra
    if(*palabra == '\0') palabra = "N/A";
    switch (indice) { // Guarda el valor en la estructura de user
      case 0:
        strncpy(user->nombre, palabra, MAX_NOMBRE);
        user->nombre[MAX_NOMBRE - 1] = '\0'; // Asegura que la cadena esté terminada en null
        break;
      case 1:
        strncpy(user->contrasena, palabra, MAX_NOMBRE);
        user->contrasena[MAX_NOMBRE - 1] = '\0';
        break;
      case 2:
        strncpy(user->ncuenta, palabra, MAX_CUENTA);
        user->ncuenta[MAX_CUENTA - 1] = '\0';
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
}
