#include "funciones.h"

void MenuOpciones(int *idUser){
  if (idUser==NULL) {
    perror("Error al pasar id de User");
    exit(-1);
  } 
  int seleccion=-1;
  system("clear");
  for (int i =0; funcionesMenu[i]!=NULL; i++) {
    printf("%d:%s\n", i+1,funcionesMenu[i]);
  }
  printf("Introduce la opcion de seleccion:\t");
  scanf("%d",&seleccion);
  switch (seleccion)
  {
    case 1:
      SacarDinero(idUser);
      break;
    case 2:
      MeterDinero(idUser);
      break;    
    case 3:
      ConsultarSaldo(idUser);
      break;
    case 4:
      InfoCuenta(idUser);
      break;
    case 5:
      Transaccion(idUser);
      break;
    case 6:
      PagarTasas(idUser);
      break;
    case 7:
      CancelarTarjeta(idUser);
      break;
    case 8:
      exit(1);
      break;
    default:
      break;
  }
}
