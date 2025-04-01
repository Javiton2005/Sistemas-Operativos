#include "comun.h"

struct _Estadisticas Estadisticas;
struct _Config Config;
void InitGlobal(){
  
  FILE *properties;
  char path[100];
  int fileIndex=0;

  Estadisticas.usuarios = 0;
  
  properties=fopen("./properties.txt", "r");
  
  if(properties==NULL){
    perror("No se a podido abrir el fichero prproperties.txt");
    return;
  }
  while (fgets(path, sizeof(path), properties)) {
    if (path[0] == '#' || strlen(path) < 3) continue;
    if (strstr(path, "LIMITE_RETIRO")) sscanf(path, "LIMITE_RETIRO=%d", &Config.limite_retiro);
    else if (strstr(path, "LIMITE_TRANSFERENCIA")) sscanf(path, "LIMITE_TRANSFERENCIA=%d", &Config.limite_transferencia);
    else if (strstr(path, "UMBRAL_RETIROS")) sscanf(path, "UMBRAL_RETIROS=%d", &Config.umbral_retiros);
    else if (strstr(path, "UMBRAL_TRANSFERENCIAS")) sscanf(path, "UMBRAL_TRANSFERENCIAS=%d", &Config.umbral_transferencias);
    else if (strstr(path, "NUM_HILOS")) sscanf(path, "NUM_HILOS=%d", &Config.num_hilos);
    else if (strstr(path, "ARCHIVO_CUENTAS")) sscanf(path, "ARCHIVO_CUENTAS=%s", Config.archivo_cuentas);
    else if (strstr(path, "ARCHIVO_LOG")) sscanf(path, "ARCHIVO_LOG=%s",Config.archivo_log);
    else if (strstr(path, "LIMITE_INTENTOS_LOGIN")) sscanf(path, "LIMITE_INTENTOS_LOGIN=%d",&Config.limite_login);
    else if (strstr(path, "ARCHIVO_TRANSFERENCIAS")) sscanf(path, "ARCHIVO_TRANSFERENCIAS=%s",Config.archivo_tranferencias);
  } 

}
