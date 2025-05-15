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


void manejar_anomalia(char *mensaje) {
  printf("BANCO: %s", mensaje);

  int codigo_anomalia = atoi(&mensaje[9]); // Extraer el código de la anomalia

  switch (codigo_anomalia) {
    case ESTADO_FONDOS_INSUFICIENTES:
      printf("BANCO: Fondos insuficientes detectados.\n");
      break;
    case ESTADO_TRANSACCION_GRANDE:
      printf("BANCO: Transacción grande detectada.\n");
      break;
    case ESTADO_LOGIN_FALLIDO:
      printf("BANCO: Login fallido detectado.\n");
      break;
    case ESTADO_SECUENCIA_INUSUAL:
      printf("BANCO: Secuencia inusual detectada.\n");
      break;
    case ESTADO_USUARIO_NO_EXISTE:
      printf("BANCO: Usuario no existe detectado.\n");
      break;
  }
}

int main(){

  key_t key = ftok("shmfile", 64);
  char *nombre = strdup("Banco");
  char salir='a';
  InitGlobal();
  printf("Inicia\n");
  int pipe_alerta[2]; // Descriptores de lectura y escritura del pipe

  if (pipe(pipe_alerta) == -1) { // Crear el pipe
    perror("Error en pipe");
    exit(EXIT_FAILURE);
  }


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
    close(pipe_alerta[0]); // Cerrar el descriptor de escritura del pipe

    char comando[256];
    char pipe[5];
    sprintf(pipe, "%d",  pipe_alerta[1]);
    snprintf(comando, sizeof(comando), "./monitor \"%s\" ", pipe);
    execlp("gnome-terminal", "gnome-terminal", "--", "sh", "-c",  comando, (char *)NULL);
    exit(0);
  } else {
    close(pipe_alerta[1]); // Cerrar el descriptor de lectura del pipe

    while (salir != '*') {
      system("clear");

      if(tabla==NULL){
        printf("Error en la creaccion de Lista de Usuarios");
        exit(-1);
      }

      login(tabla, shm_id); // Lanzar el proceso login (JAIME: LO HE PUESTO PARA QUE SE EJECUTE EL LOGIN BORRARLO SI LO HACEIS DE OTRA FORMA)
      
      // Leer anomalias desde el pipe

      char buffer[256];
      while (read(pipe_alerta[0], buffer, sizeof(buffer)) > 0) {
        manejar_anomalia(buffer);
      }

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
