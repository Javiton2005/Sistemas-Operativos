#include "funciones.h"
#include <stdio.h>

void MenuOpciones(int *idUser){

  if (idUser==NULL) {
    perror("Error al pasar id de User");
    exit(-1);
  } 
  int seleccion=-1;
  system("clear");
  for (int i =0; funcionesMenu[i]!=NULL; i++) {
    printf("%d:%s\n", i,funcionesMenu[i]);
  }
  printf("Introduce la opcion de seleccion:\t");
  scanf("%d",&seleccion);
  switch (seleccion)
  {
    case 0:
      SacarDinero(idUser);
      break;
    case 1:
      MeterDinero(idUser);
      break;    
    case 2:
      ConsultarSaldo(idUser);
      break;
    case 3:
      InfoCuenta(idUser);
      break;
    case 4:
      Transaccion(idUser);
      break;
    case 5:
      PagarTasas(idUser);
      break;
    case 6:
      CancelarTarjetas(idUser);
      break;
    case 7:
      exit(1);
      break;
    default:
      break;
  }
}
