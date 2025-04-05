#include "comun.h"

USER *LeerCSVNcuenta(char *ncuenta){
  int i;
  FILE *db;
  char *line = malloc(256);
  USER *user=malloc(sizeof(USER));
  if (user==NULL) {
    perror("Error al alocar memoria");
    exit(-1);
  }
  db = fopen(Config.archivo_cuentas, "rb");
  fgets(line, sizeof(line), db);
  //Bucle para buscar al usuario en funcion de su numero de cuenta
  while((fgets(line, 255, db))!=NULL){
    i++;
    user->nombre = strsep(&line, ";");
    user->contrasena = strsep(&line, ";");
    user->ncuenta = strsep(&line, ";");
    if (strcmp(user->ncuenta, ncuenta)){
      user->saldo = atof(strsep(&line, ";"));
      user->id = i;
      fclose(db);
      return(user);
    }
  }
  free(user);
  fclose(db);
  return(NULL);
}
