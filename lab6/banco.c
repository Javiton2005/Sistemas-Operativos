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

  int pipe_alerta[2]; // Descriptores de lectura y escritura del pipe

  if (pipe(pipe_alerta) == -1) { // Crear el pipe
    perror("Error en pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork(); // Crear un proceso hijo

  if (pid < 0) { // Comprobar si ha habido error
    perror("Error en fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    close(pipe_alerta[1]); // Cerrar el descriptor de escritura del pipe
    monitor(pipe_alerta[0]); // Lanzar el proceso monitor
    exit(0);
  } else {
    close(pipe_alerta[0]); // Cerrar el descriptor de lectura del pipe

    while (salir!='*') {
      system("clear");
      listaUsuarios=CrearListaUsuarios(Config.archivo_cuentas);
      if(listaUsuarios==NULL){
        printf("Error en la creaccion de Lista de Usuarios");
        exit(-1);
      }
      
      char alerta[256];
      ssize_t alerta_size = read(pipe_alerta[0], alerta, sizeof(alerta)-1);
      if (alerta_size > 0) {
        alerta[alerta_size] = '\0';
        printf("ALERTA: %s\n", alerta);
      } else {
        perror("read");
      }

      printf("Para salir presiona *: ");
      while (getchar() != '\n'); // Limpiamos el buffer de entrada
      salir=getchar();
    }

    close(pipe_alerta[0]); // Cerrar el descriptor de escritura del pipe
  }
  
  return 1;
}
