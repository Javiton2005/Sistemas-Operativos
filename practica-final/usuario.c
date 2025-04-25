#include "comun/comun.h"
#include "funciones/funciones.h"
int memid;
int main(int argc, char *argv[]){
  int idUser=atoi(argv[1]);
  memid = atoi(argv[2]);
  InitGlobal(); 
  while (1) {  
    MenuOpciones(&idUser, memid);
  }
}
