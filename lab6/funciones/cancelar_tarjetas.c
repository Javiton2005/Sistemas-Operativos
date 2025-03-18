#include "funciones.h"

void *CancelarTarjetas(void *usuario){
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


}
