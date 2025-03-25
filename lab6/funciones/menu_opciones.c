#include "funciones.h"
#include <stdio.h>

void *MenuOpciones(void *registrado){

  int *codigoRetorno = malloc(sizeof(int));
  if (codigoRetorno == NULL)
    return NULL;

  if (registrado == NULL) {
      *codigoRetorno = 1;
      return codigoRetorno;
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
      SacarDinero(registrado,1);
      break;
    case 1:
      MeterDinero(registrado);
      break;    
    case 2:
      ConsultarSaldo(registrado);
      break;
    case 3:
      InfoCuenta(registrado);
      break;
    case 4:
      Transaccion(registrado);
      break;
    case 5:
      PagarTasas(registrado);
      break;
    case 6:
      CancelarTarjetas(registrado);
      break;
    case 7:
      exit(1);
      break;
    default:
      break;
  }

  *codigoRetorno=0;
  return codigoRetorno;
}

