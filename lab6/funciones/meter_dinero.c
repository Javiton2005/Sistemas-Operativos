#include "funciones.h"

int MeterDinero(){
    float c;
    printf("Cantidad a ingresar: \n");
    scanf("%f", &c);
    if (c > 0){
        printf("Formato incorrecto\n");
        return(1);
    }
    if (c > MAX_TRANSACCION){
        printf("Cantidad excede el limite establecido en este banco\n");
        return(2);
    }
    printf("Iniciando ingreso\n");
    user->saldo = user->saldo + c;
    TRANSACCION transaccion;
    time_t t;
    transaccion.cantidad = c;
    transaccion.ncuentas = user->ncuenta;
    transaccion.ncuentao = NULL;
    time(&t);
    transaccion.fecha = localtime(&t);
    ModificarCSV(user);
    printf("Ingreso completado\n");
    return(0);
}