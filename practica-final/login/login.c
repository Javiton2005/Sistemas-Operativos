/*
* Recibe una lista de usuarios y llama a una terminal externa con otro programa
*
* Se recorre toda la lista de usuarios buscando una coincidencia de las credenciales
*/

#include "login.h"
#include <stdio.h>



void login(TABLA_USUARIOS *listaUsuarios, int memid){

  char nombre[MAX_NOMBRE];
  char contrasena[MAX_NOMBRE];
  FILE *banco;
  char mensaje[256];
  time_t t;
  struct tm *tm_info;
  char fecha[50];

  // El usuario introduce sus credenciales
  printf("Inserta Nombre de la cuenta: ");
  scanf("%s", nombre);

  printf("Inserta Contraseña de la cuenta: ");
  scanf("%s", contrasena);
  for(int i =0;i<listaUsuarios->num_usuarios;i++){
    //printf("Comparado con: %s, %s",listaUsuarios[i]->nombre,listaUsuarios[i]->contrasena);
    // Si las credenciales conciden entra en el stament
    if (strncmp(nombre, listaUsuarios->usuarios[i].nombre, MAX_NOMBRE)==0 && strncmp(contrasena, listaUsuarios->usuarios[i].contrasena, MAX_NOMBRE)==0) {
      while ((Config.fd_escritura_inicio = open(FIFO_INICIO, O_WRONLY)) == -1) {
        perror("Banco: Error al abrir el FIFO para escritura. Intentando de nuevo...");
        sleep(1); // Esperar un poco antes de reintentar
      }
      int numerocuenta=atoi(listaUsuarios->usuarios[i].ncuenta);
      if (write(Config.fd_escritura_inicio, &numerocuenta, sizeof(int)) == -1) {
          perror("Banco: Error al escribir en el FIFO");
          break; // Salir del bucle si hay un err(EXIT_FAILURE, "%s");or de escritura
      } 
      pid_t pid = fork(); // Se duplica para que el hijo pueda morir sin que el proceso padre pueda seguir ejecutando
      if (pid == 0) {  // Proceso hijo

        char comando[256];
        snprintf(comando, sizeof(comando), "./usuario \"%d\" \"%d\"", listaUsuarios->usuarios[i].id, memid);

        if (access("/bin/gnome-terminal", X_OK) == 0) { //Comprueba si la terminal gnome existe, si es asi la ejecuta y si no ejecuta kitty
          execlp("gnome-terminal", "gnome-terminal", "--", "sh", "-c",  comando, (char *)NULL);
        }
        else {
          execlp("kitty", "kitty", "sh", "-c", comando, (char *)NULL); 
        }
        perror("Error al ejecutar una termianal");
        
        exit(-1);
      }

      // Crea el mensaje del para escribir en ellog
      snprintf(mensaje, sizeof(mensaje),"Usuario:%s ha hecho log in con la contraseña %s", listaUsuarios->usuarios[i].nombre,listaUsuarios->usuarios[i].contrasena);
      EscribirEnLog(mensaje);
      return;
    }
  }
  // Crea el mensaje del para escribir en ellog
  snprintf(mensaje, sizeof(mensaje), "[Warning]Intento inicio de sesion: Usuario:%s Contraseña:%s", nombre, contrasena);
  EscribirEnLog(mensaje);
  printf("Las credenciales introducidas con coinciden con ningun usuario\n");
  return;
}
