#include "funciones.h"

void CancelarTarjeta(int *idUser){
  char *n;
  printf("Ingrese el nuevo numero de cuenta quiera tener: \n");
  scanf("%s",n);
  IdValor parametros = {idUser, n};
}
void CancelarTarjetaHilo(void *valor){
  IdValor *parametros = (IdValor*)valor;
  USER *user = leerCsv(parametros->id);
  printf("Iniciando cancelacion de tarjeta\n");
  user->ncuenta = (parametros->valor);
  EditarCsv(user);
  printf("Tarjeta cancelada\n");
  printf("Se le ha asignado una nueva\n");
  return;
}
