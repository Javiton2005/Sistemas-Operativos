#include "comun.h"

USER *LeerCSVNcuenta(char *ncuenta){
  int i;
  FILE *db;
  char *line;
  USER *user=malloc(sizeof(USER));
  if (user==NULL) {
    perror("Error al alocar memoria");
    exit(-1);
  }
  db = fopen(Config.archivo_cuentas, "rb");
  fgets(line, 256, db);
  //Bucle para buscar al usuario en funcion de su numero de cuenta
  while((line = fgets(line, 256, db))!=NULL){
    i++;
    user->nombre = strtok(line, ";");
    user->contrasena = strtok(line, NULL);
    user->ncuenta = strtok(line, NULL);
    if (user->ncuenta == ncuenta){
      user->saldo = atof(strtok(line, NULL));
      user->id = i;
      fclose(db);
      return(user);
    }
    fclose(db);
    return(NULL);
  }
}
