#include "funciones.h"

int ConsultarSaldo(USER *usuario){

    if(usuario==NULL){
        return 4;
    }
    if (strcmp(usuario->nombre, "\0")==0)
    {
        return 6;
    }
    if (usuario->saldo<=-1)
    {
        return 2;
    }    

    printf("El saldo de la cuenta de %s\n",usuario->nombre);
    printf("Saldo: %d\n", usuario->saldo);
    
    return 0;

}
