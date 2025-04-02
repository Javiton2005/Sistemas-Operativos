#include "comun.h"
#include <stdio.h>

USER *LeerCSVNcuenta(char *ncuenta){
  FILE *db;
  char *line;
  USER *user=malloc(sizeof(USER));
  if (user==NULL) {
    perror("Error al alocar memoria");
    exit(-1);

  }
  db = fopen("../ficheros/db.csv", "r");
  fgets(line, 256, db);
  while((line = fgets(line, 256, db))!=NULL){
    user->nombre = strtok(line, ";");
    user->contrasena = strtok(line, NULL);
    user->ncuenta = strtok(line, NULL);
    if (user->ncuenta == ncuenta){
      user->saldo = atof(strtok(line, NULL));
      user->ntransacciones = atoi(strtok(line, NULL));
      //añadir linea de usuario y estructura de transacciones
      fclose(db);
      return(user);
    }
    fclose(db);
    return(NULL);
  }
  return user;
}
