#include "comun.h"

USER LeerCSV(int ncuenta){
  FILE *db;
  char *line;
  USER user;
  db = fopen("../ficheros/db.csv", "r");
  fgets(line, 256, db);
  while((line = fgets(line, 256, db))!=NULL){
    user.nombre = strtok(line, ";");
    user.contrasena = strtok(line, NULL);
    user.ncuenta = strtok(line, NULL) - '0';
    if (user.ncuenta == ncuenta){
      user.saldo = strtok(line, NULL) - '0';
      user.ntransacciones = strtok(line, NULL) - '0';
      //añadir linea de usuario y estructura de transacciones
      fclose(db);
      return(user);
    }
    fclose(db);
    return(NULL);
  }
}