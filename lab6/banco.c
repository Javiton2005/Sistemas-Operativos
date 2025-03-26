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
#include "monitor/monitor.h"
#include <stdio.h>


int main(){

  USER **listaUsuarios=NULL;
  char salir='a';
  InitGlobal();

  int fd[2]; // Descriptores de lectura y escritura del pipe

  if (pipe(fd) == -1) { // Crear el pipe
    perror("Error en pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork(); // Crear un proceso hijo

  if (pid < 0) { // Comprobar si ha habido error
    perror("Error en fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    close(fd[1]); // Cerrar el descriptor de escritura del pipe
    monitor(fd[0]); // Lanzar el proceso monitor
    exit(0);
  } else {
    close(fd[0]); // Cerrar el descriptor de lectura del pipe

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

    close(fd[1]); // Cerrar el descriptor de escritura del pipe
  }
  
  return 1;
}
