#include "funciones.h"

void sacarDinero()
{
    printf("-- Sacar Dinero --\n");    
    printf("Introduce la cantidad a sacar: ");
    scanf("%f", &cantidad);

    if (cantidad > saldo) {
        printf("No tienes suficiente saldo\n");
    } else {
        saldo -= cantidad;
        printf("Has sacado %.2f euros\n", cantidad);
        printf("Tu saldo actual es de %.2f euros\n", saldo);
    }
    printf("\n");
}
