#include "funciones.h"

int InfoCuenta(USER *usuario){

    printf("El informacion de la cuenta: %s", usuario->nombre);
    printf("Numero de la cuenta: %d", usuario->ncuenta);
}