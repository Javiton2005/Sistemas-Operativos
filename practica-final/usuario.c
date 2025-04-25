#include "comun/comun.h"
#include "funciones/funciones.h"
#include <stdio.h>
int memid;
int main(int argc, char *argv[]){
  int idUser=atoi(argv[1]);
  memid = atoi(argv[2]);
  getchar();
  while (getchar()!='\n'){}
  InitGlobal(); 
  while (1) {  
    MenuOpciones(&idUser, memid);
  }
}
