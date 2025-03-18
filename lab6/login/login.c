#include "login.h"
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <time.h>

// Se cogen las variables globales del main
extern int hilosCount;
extern pthread_mutex_t lock;

void *login(USER **listaUsuarios, pthread_t *hilos){

  char nombre[50];
  char contraseña[50];
  int i=0;
  int *ret;
  printf("Inserta Nombre de la cuenta: ");
  scanf("%s", nombre);

  printf("Inserta Contraseña de la cuenta: ");
  scanf("%s", contraseña);
  
  for(i =0;i<Estadisticas.usuarios;i++){
    if (strcmp(nombre, listaUsuarios[i]->nombre)==0 && strcmp(contraseña, listaUsuarios[i]->contrasena)==0) {
      pthread_mutex_lock(&lock);
      hilos=realloc(hilos,sizeof(pthread_t)*hilosCount+1);
      
      if (hilos==NULL) {
        perror("Error al asignar memoria\n");
        exit(0);
      }

      ret = &hilosCount-1;
      hilosCount++;

      pthread_mutex_unlock(&lock);
      pthread_create(hilos+hilosCount-1, NULL, MenuOpciones, listaUsuarios[i]); 
      
      return ret;
    }
  }
  ret=NULL;
  return ret;
}
