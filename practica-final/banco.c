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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

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
  char *nombre = strdup("Banco", nombre);
  USER **listaUsuarios=NULL;
  char salir='a';
  InitGlobal();
  int pipe_alerta[2]; // Descriptores de lectura y escritura del pipe

  if (pipe(pipe_alerta) == -1) { // Crear el pipe
    perror("Error en pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork(); // Crear un proceso hijo

  listaUsuarios = CrearListaUsuarios(Config.archivo_cuentas);
  
  /*int memid=shm_open(nombre, O_CREAT | O_RDWR, 0666);
  if (memid == -1) {
    perror("Error al crear la memoria compartida");
    exit(EXIT_FAILURE);
  }
  if (ftruncate(memid, sizeof(USER) * Estadisticas.usuarios) == -1) {
    perror("Error al truncar la memoria compartida");
    exit(EXIT_FAILURE);
  }
  USER **usuario = (USER **)mmap(NULL, sizeof(USER) * Estadisticas.usuarios, PROT_READ | PROT_WRITE, MAP_SHARED, memid, 0);
  if (usuario == NULL) {
    perror("Error al mapear la memoria compartida");
    exit(EXIT_FAILURE);
  }
  // Copiar la lista de usuarios a la memoria compartida
  for (int i = 0; i < Estadisticas.usuarios; i++) {
    if (listaUsuarios[i] != NULL) {
      usuario[i]->id = listaUsuarios[i]->id;
      strcpy(usuario[i]->nombre, listaUsuarios[i]->nombre);
      strcpy(usuario[i]->contrasena, listaUsuarios[i]->contrasena);
      strcpy(usuario[i]->ncuenta, listaUsuarios[i]->ncuenta);
      usuario[i]->saldo = listaUsuarios[i]->saldo;
    }
  }*/
  
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

      if(listaUsuarios==NULL){
        printf("Error en la creaccion de Lista de Usuarios");
        exit(-1);
      }

      login(listaUsuarios, memid); // Lanzar el proceso login (JAIME: LO HE PUESTO PARA QUE SE EJECUTE EL LOGIN BORRARLO SI LO HACEIS DE OTRA FORMA)
      
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
  }
  
  return 1;
}
