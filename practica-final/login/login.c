/*
* Recibe una lista de usuarios y llama a una terminal externa con otro programa
*
* Se recorre toda la lista de usuarios buscando una coincidencia de las credenciales
*/

#include "login.h"
#include <stdio.h>



void login(USER **listaUsuarios, int memid){

  char nombre[50];
  char contrasena[50];
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
   
  for(int i =0;i<Estadisticas.usuarios;i++){
    //printf("Comparado con: %s, %s",listaUsuarios[i]->nombre,listaUsuarios[i]->contrasena);
    // Si las credenciales conciden entra en el stament
    if (strcmp(nombre, listaUsuarios[i]->nombre)==0 && strcmp(contrasena, listaUsuarios[i]->contrasena)==0) {
      pid_t pid = fork(); // Se duplica para que el hijo pueda morir sin que el proceso padre pueda seguir ejecutando
      if (pid == 0) {  // Proceso hijo
        // Convertimos edad y dinero a cadenas
        char idStr[5];
        sprintf(idStr, "%d", listaUsuarios[i]->id);
        
        char memidStr[20];
        sprintf(memidStr, "%d", memid);
        char comando[256];
        snprintf(comando, sizeof(comando), "./usuario \"%s\" \"%s\"", idStr, memidStr);

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
      snprintf(mensaje, sizeof(mensaje),"Usuario:%s ha hecho log in con la contraseña %s", listaUsuarios[i]->nombre,listaUsuarios[i]->contrasena);
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
