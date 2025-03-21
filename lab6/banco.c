#include "comun/comun.h"
#include "usuarios/usuarios.h"
#include "login/login.h"
#include <stdio.h>


int main(){

  USER **listaUsuarios=NULL;
  char salir;
  InitGlobal();

  while (salir!='*') {
    system("clear");
    listaUsuarios=CrearListaUsuarios(Config.archivo_cuentas);

    login(listaUsuarios);
    printf("Para salir presiona *: ");
    while (getchar() != '\n'); // Limpiamos el buffer de entrada
    salir=getchar();
  }
  
  return 1;
}
