/*
 * Banco es el proceso principal del banco
 <<<<<<< HEAD
=======
  int codigo_anomalia = atoi(&mensaje[9]); // Extraer el código de la anomalia

  switch (codigo_anomalia) {
    case ESTADO_FONDOS_INSUFICIENTES:
      printf("BANCO: Fondos insuficientes detectados.\n");
      break;
    case ESTADO_TRANSACCION_GRANDE:
      printf("BANCO: Transacción grande detectada.\n");
      break;
    case ESTADO_CONSTRASEÑA_INCORRECTA:
      printf("BANCO: Contraseña incorrecta detectada.\n");
      break;
    case ESTADO_TRANSACCION_INTERNACIONAL:
      printf("BANCO: Transacción internacional detectada.\n");
      break;
    case ANOMALIA_SECUENCIA_INUSUAL:
      printf("BANCO: Secuencia inusual detectada.\n");
      break;
    case ESTADO_USUARIO_NO_EXISTE:
      printf("BANCO: Usuario no existe detectado.\n");
      break;
    default:
      printf("BANCO: Anomalía desconocida.\n");
      break; // No se si el break causara un error
  }
}

>>>>>>> 78393f9db4622b07e8db9585005fb396e271e9e4*
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
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

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
  } else if (pid == 0) {
    close(pipe_alerta[0]); // Cerrar el descriptor de escritura del pipe
    monitor(pipe_alerta[1]); // Lanzar el proceso monitor
    exit(0);
  } else {
    close(pipe_alerta[1]); // Cerrar el descriptor de lectura del pipe

    while (salir != '*') {
      system("clear");
      listaUsuarios = CrearListaUsuarios(Config.archivo_cuentas);
      if(listaUsuarios==NULL){
        printf("Error en la creaccion de Lista de Usuarios");
        exit(-1);
      }

      login(listaUsuarios); // Lanzar el proceso login (JAIME: LO HE PUESTO PARA QUE SE EJECUTE EL LOGIN BORRARLO SI LO HACEIS DE OTRA FORMA)
      
      // Leer anomalias desde el pipe

      char buffer[256];
      while (read(pipe_alerta[0], buffer, sizeof(buffer)) > 0) {
        manejar_anomalia(buffer);
      }

      printf("Para salir presiona *: ");
      while (getchar() != '\n'); // Limpiamos el buffer de entrada
      salir=getchar();
    }

    wait(NULL); // Esperar a que el proceso monitor.c termine
  }
  
  return 1;
}

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
    case ESTADO_CONSTRASEÑA_INCORRECTA:
      printf("BANCO: Contraseña incorrecta detectada.\n");
      break;
    case ESTADO_TRANSACCION_INTERNACIONAL:
      printf("BANCO: Transacción internacional detectada.\n");
      break;
    case ANOMALIA_SECUENCIA_INUSUAL:
      printf("BANCO: Secuencia inusual detectada.\n");
      break;
    case ESTADO_USUARIO_NO_EXISTE:
      printf("BANCO: Usuario no existe detectado.\n");
      break;
    default:
      printf("BANCO: Anomalía desconocida.\n");
      break; // No se si el break causara un error
  }
}