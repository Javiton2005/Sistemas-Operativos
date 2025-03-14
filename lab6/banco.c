#include "comun/comun.h"
#include "login/login.h"
#include "usuarios/usuarios.h"
#include "funciones/funciones.h"
#include <stdio.h>


#define MAX_LEN_FICHERO 100 

FILE *properties;

int main(){
  char path[MAX_LEN_FICHERO];
  int fileIndex=0;
  char *dbFile;
  char *bancoFile;
  USER **listaUsuarios=NULL;
  USER *registrado;
  void *tmp;
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
  

  tmp=login(listaUsuarios);
  


  if(tmp==NULL)
    exit(1);


  registrado=(USER*)tmp;
  MenuOpciones(registrado);
  return 1;
}
