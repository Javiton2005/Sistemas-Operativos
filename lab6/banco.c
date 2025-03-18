#include "comun/comun.h"
#include "usuarios/usuarios.h"
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include "login/login.h"

#define MAX_LEN_FICHERO 100 


int hilosCount=0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int main(){
  char path[MAX_LEN_FICHERO];
  FILE *properties;
  int fileIndex=0;
  char *dbFile;
  char *bancoFile;
  USER **listaUsuarios=NULL;
  USER *registrado;
  void *tmp;
  int *usado;
  pthread_t *hilos = malloc(sizeof(pthread_t));
  
  InitGlobal();
  properties=fopen("./properties.txt", "r");
  
  if(properties==NULL){
    perror("No se a podido abrir el fichero prproperties.txt");
    return (1);
  }

  while (fgets(path, MAX_LEN_FICHERO, properties)!=NULL) {  
    path[strlen(path)-1]='\0';
    switch (fileIndex) {
      case 0:
        dbFile=strdup(path);
        break;
      case 1:
        bancoFile=strdup(path);
        break;
    }
    fileIndex++;
  }
  listaUsuarios=CrearListaUsuarios(dbFile);

  tmp = login(listaUsuarios, hilos);
  
  if(tmp!=NULL || tmp != 0){
    for (int i=0; i<=*(int *)tmp; i++) {
      pthread_join(hilos[i], NULL);
    }
  }
  return 1;
}
