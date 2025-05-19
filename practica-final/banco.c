/*
 * Banco es el proceso principal del banco
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

  key_t key = ftok("shmfile", 64);
  char salir='a';
  InitGlobal();

  int shm_id = shmget(IPC_PRIVATE, sizeof(TABLA_USUARIOS), IPC_CREAT | 0666);
  if (shm_id == -1) {
    perror("Error al crear la memoria compartida");
    exit(EXIT_FAILURE);
  }
  TABLA_USUARIOS *tabla = (TABLA_USUARIOS*)shmat(shm_id, NULL, 0);
  if (tabla == NULL) {
    perror("Error al mapear la memoria compartida");
    exit(EXIT_FAILURE);
  }
  memset(tabla, 0, sizeof(TABLA_USUARIOS)); // Inicializar la tabla de usuarios

  CrearListaUsuarios(tabla, Config.archivo_cuentas); // Crear la lista de usuarios


  pid_t pid = fork(); // Crear un proceso hijo

  if (pid < 0) { // Comprobar si ha habido error
    perror("Error en fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {

    char comando[256];
    char pipe[5];
    snprintf(comando, sizeof(comando), "./monitor \"%s\" ", pipe);
    execlp("gnome-terminal", "gnome-terminal", "--", "sh", "-c",  comando, (char *)NULL);
    exit(0);
  } else {

    while (salir != '*') {
      system("clear");

      if(tabla==NULL){
        printf("Error en la creaccion de Lista de Usuarios");
        exit(-1);
      }

      login(tabla, shm_id); // Lanzar el proceso login (JAIME: LO HE PUESTO PARA QUE SE EJECUTE EL LOGIN BORRARLO SI LO HACEIS DE OTRA FORMA)
      
      // Leer anomalias desde el pipe      
      printf("Presione \\n o para salir presiona *: ");
      while (getchar() != '\n'); // Limpiamos el buffer de entrada
      salir=getchar();
    }

    wait(NULL); // Esperar a que el proceso monitor.c termine
    
    // Desadjuntar la memoria compartida
    if (shmdt(tabla) == -1) perror("Error al desadjuntar la memoria compartida");
    // Eliminar el segmento de memoria compartida
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) perror("Error al eliminar la memoria compartida");

  }
  
  return 1;
}
