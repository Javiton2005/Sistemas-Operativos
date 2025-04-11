#include "comun.h"
#include <stdio.h>

int *LeerCSVNcuenta(char *ncuenta){
  
  int *i=calloc(1,sizeof(int));
  *i=1;
  FILE *db;
  char line[255];
  USER *user=malloc(sizeof(USER));
  if (user==NULL) {
    perror("Error al alocar memoria");
    exit(-1);
  }
  db = fopen(Config.archivo_cuentas, "rb");
  if(!db){
    perror("error al abrir el fichero");
    exit(-1);
  }
  fgets(line, sizeof(line), db);

  //Bucle para buscar al usuario en funcion de su numero de cuenta
  while(fgets(line, sizeof(line), db)!=NULL){
    char *ptr=line;
    user->nombre = strsep(&ptr, ";");
    user->contrasena = strsep(&ptr, ";");
    user->ncuenta = strsep(&ptr, ";");
    if (strcmp(user->ncuenta, ncuenta)==0){
      fclose(db);
      return(i);
    }
    *i+=1;
  }
  free(i);
  free(user);
  fclose(db);
  return(NULL);
}
