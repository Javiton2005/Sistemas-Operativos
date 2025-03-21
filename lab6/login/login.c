#include "login.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>


void login(USER **listaUsuarios){

  char nombre[50];
  char contraseña[50];
  FILE *banco;
  char mensaje[256];
  time_t t;
  struct tm *tm_info;
  char fecha[50];

  printf("Inserta Nombre de la cuenta: ");
  scanf("%s", nombre);

  printf("Inserta Contraseña de la cuenta: ");
  scanf("%s", contraseña);
  
  for(int i =0;i<Estadisticas.usuarios;i++){
    if (strcmp(nombre, listaUsuarios[i]->nombre)==0 && strcmp(contraseña, listaUsuarios[i]->contrasena)==0) {
      pid_t pid = fork();
      if (pid == 0) {  // Proceso hijo
        // Convertimos edad y dinero a cadenas
        char nTransaccionesStr[50];
        char saldoStr[50];
        sprintf(nTransaccionesStr, "%d", listaUsuarios[i]->ntrasacciones);
        sprintf(saldoStr, "%d", listaUsuarios[i]->saldo);
        
        char comando[256];
        snprintf(comando, sizeof(comando), "./usuario \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" ", listaUsuarios[i]->nombre, listaUsuarios[i]->contrasena, listaUsuarios[i]->ncuenta,saldoStr ,nTransaccionesStr, Config.archivo_log);

        if (access("/bin/gnome-terminal", X_OK) == 0) { //Comprueba si la terminal gnome existe, si es asi la ejecuta y si no ejecuta kitty
          execlp("gnome-terminal", "gnome-terminal", "--", "sh", "-c",  comando, (char *)NULL);
        }
        else {
          execlp("kitty", "kitty", "sh", "-c", comando, (char *)NULL); 
        }
        perror("Error al ejecutar una termianal");
        
        exit(-1);
      }
      
      t = time(NULL); 
      tm_info = localtime(&t);

      strftime(fecha, sizeof(fecha), "%d-%m-%Y %H:%M:%S", tm_info);
      snprintf(mensaje, sizeof(mensaje),"%s Usuario:%s ha hecho log in con la contraseña %s\n", fecha, listaUsuarios[i]->nombre,listaUsuarios[i]->contrasena);
      // Bloquea el sistema por medio de semaforos
      sem_t *semaforo = sem_open("/semaforo_log", O_CREAT, 0644, 1);
      banco = fopen(Config.archivo_log,"a");
      fputs(mensaje, banco);
      fclose(banco);
      sem_post(semaforo);
      return;
    }
  }
  printf("Las credenciales introducidas con coinciden con ningun usuario\n");
  return;
}
