#include "funciones.h"

int CancelarTarjeta(int *idUser){
  char *np;
  printf("Ingrese el nuevo pin que quiera tener en la tarjeta: \n");
  scanf("%s",np);
  IdValor parametros = {idUser, np};

}
void CancelarTarjetaHilo(void *valor){
  IdValor *parametros = (IdValor*)valor;
  USER *user = leerCsv(parametros->id);
  printf("Iniciando cancelacion de tarjeta\n");
  for(int i=0;i < 16;i++){
    //user->ntarjeta[i] = (random() * 10) + '0';
  }
  //user->pin = np;
  ModificarCSV(user);
  printf("Tarjeta cancelada\n");
  printf("Se le ha asignado una nueva\n");
  return;
}