#include "comun/comun.h"
#include "funciones/funciones.h"

int main(int argc, char *argv[]){
  int idUser=atoi(argv[1]);
  InitGlobal(); 
  while (1) {  
    MenuOpciones(&idUser);
  }
}
