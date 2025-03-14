#include "funciones.h"
int transaccion(){
  int nc, b=0, c;
  printf("Nº de cuenta al que se le quiera hacer la trnasacción: \n");
  scanf("%d\n", %nc);
  if (nc < 0){
    printf("Nº de cuenta no existe\n");
    return(1);
  }
  for (int i=0;i<Estadisticas.usuarios;i++) if (nc == listausuarios[i]) b++;
  if (b > 1){
    printf("Hay varias cuentas con ese numero de cuenta\n");
    return(2);
  }
  else if(b < 1){
    printf("No existe ese numero de cuenta\n");
    return(3);
  }
  printf("¿Que cantidad quiere transferir? \n");
  scanf("%d", &c);
  if (c < 0){
    printf("Formato incorrecto");
    return(4);
  }
  //TO DO
  return(0);
}
