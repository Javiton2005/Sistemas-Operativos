#include "funciones.h"

void *ConsultarSaldo(void *usuario){

  if(usuario==NULL){
      return (void *)4;
  }
  USER *user = (USER *)usuario;
  if (strcmp(user->nombre, "\0")==0)
  {
      return (void *)6;
  }
  if (user->saldo<=-1)
  {
      return (void *)2;
  }    

  printf("El saldo de la cuenta de %s\n",user->nombre);
  printf("Saldo: %d\n", user->saldo);
  
  return 0;
}
