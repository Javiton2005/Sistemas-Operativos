#include "funciones.h"

int CancelarTarjeta(){
  char *c, *p, *np;
  printf("Se requiere contraseña para realizar esta operacion: \n");
  scanf("%s", c);
  printf("Se requiere pin de tarjeta para realizar esta operacion: \n");
  scanf("%s",p);
  printf("Ingrese el nuevo pin que quiera tener en la tarjeta: \n");
  scanf("%s",np);
  printf("Iniciando cancelacion de tarjeta\n");
  for(int i=0;i < 16;i++){
    user->ntarjeta[i] = (random() * 10) + '0';
  }
  user->pin = np;
  ModificarCSV(user);
  printf("Tarjeta cancelada\n");
  printf("Se le ha asignado una nueva\n");
  return(0);
}