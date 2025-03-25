#include "comun/comun.h" 
#include "funciones/funciones.h"

int main(int argc, char *argv[]){
  USER usuario = {argv[1],argv[2],argv[3],atoi(argv[4]),atoi(argv[5]),atoi(argv[6])};   
  char *log=argv[7];

  while (1) {  
    MenuOpciones(&usuario);
  }
}
