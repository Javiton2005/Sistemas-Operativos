/*
 * Banco es el proceso principal del banco
 *
 * Es un bucle que crea la lista de usuarios 
 * y se la pasa al proceso de log in
 * en el caso de que el usuario inserte * el
 * proceso acaba.
 *
*/


#include "comun/comun.h"
#include "usuarios/usuarios.h"
#include "login/login.h"
#include <stdio.h>


int main(){

  USER **listaUsuarios=NULL;
  char salir='a';
  InitGlobal();

  while (salir!='*') {
    system("clear");
    listaUsuarios=CrearListaUsuarios(Config.archivo_cuentas);
    if(listaUsuarios==NULL){
      printf("Error en la creaccion de Lista de Usuarios");
      exit(-1);
    }
    
    //printf("nombre: %s\nContraseña %s",listaUsuarios[Estadisticas.usuarios]->nombre,listaUsuarios[Estadisticas.usuarios]->contrasena);

    login(listaUsuarios);
    printf("Para salir presiona *: ");
    while (getchar() != '\n'); // Limpiamos el buffer de entrada
    salir=getchar();
  }
  
  return 1;
}
