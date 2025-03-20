#include "funciones.h"

int transaccion(){
  int nc, b=0;
  float c;
  printf("Nº de cuenta al que se le quiera hacer la transacción: \n");
  scanf("%d", %nc);
  if (nc < 0){
    printf("Nº de cuenta no existe\n");
    return(1);
  }
  USER **listaUsuarios = CrearListaUsuarios("./ficheros/db.csv");
  for (int i=0;i<Estadisticas.usuarios;i++) if (nc == listaUsuarios[i]->ncuenta) b++;
  USER o;
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
    printf("Formato incorrecto\n");
    return(4);
  }
  if (c > MAX_TRANSACCION){
    printf("Cantidad excede el limite establecido en este banco\n");
  }
  printf("Iniciando transaccion\n");
  user->saldo = user->saldo - c;
  o.saldo = o.saldo + c;
  TRANSACCION transaccion;
  time_t t;
  transaccion.cantidad = c;
  transaccion.ncuentas = user->ncuenta;
  transaccion.ncuentao = o.ncuenta;
  time(&t);
  transaccion.fecha = localtime(&t);

  printf("Transaccion completada\n");
  return(0);
}
