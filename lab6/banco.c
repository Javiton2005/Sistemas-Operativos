#include "banco/banco.h"

#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <threads.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>

#define MAX_LEN_FICHERO 100 

FILE *properties;

int main(){
  char path[MAX_LEN_FICHERO];
  int fileIndex=0;
  char *userFile;
  char *dbFile;
  char *bancoFile;


  properties=fopen("./properties.txt", "r");
  if(properties==NULL){
    perror("No se a podido abrir el fichero prproperties.txt");
    return (1);
  }

  while (fgets(path, MAX_LEN_FICHERO, properties)!=NULL) {
    switch (fileIndex) {
      case 0:
        userFile=strdup(path);
        break;
      case 1:
        dbFile=strdup(path);
        break;
      case 2:
        bancoFile=strdup(path);
        break;
      default:
        //printf("Se ha leido mas lineas de las debidas: %s", path);
        break;
    }
    fileIndex++;
  }

  printf("%s", userFile);
  printf("%s", dbFile);
  printf("%s", bancoFile);

  return 1;
}
