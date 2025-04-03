#include "funciones.h"

void MeterDinero(int *idUser){
    float c;
    pthread_t h;
    printf("Cantidad a ingresar: \n");
    scanf("%f", &c);
    if (c > 0){
        printf("Formato incorrecto\n");
        return;
    }
    if (c > Config.limite_transferencia){
        printf("Cantidad excede el limite establecido en este banco\n");
        return;
    }
    IdValor parametros = {idUser, &c};
    pthread_create(&h , NULL , MeterDineroHilo , &parametros);
    return;
}
void MeterDineroHilo(void *valor){
    IdValor *parametros = (IdValor*)valor;
    printf("Iniciando ingreso\n");
    sem_t *semaforo = sem_open("/semaforo_dbcsv", O_CREAT, 0644, 1);
    USER *user = leerCsv(*(parametros->id));
    user->saldo = user->saldo + (*(float*)(parametros->valor));
    TRANSACCION transaccion;
    time_t t;
    transaccion.cantidad = (*(float*)(parametros->valor));
    transaccion.ncuentas = user->ncuenta;
    transaccion.ncuentao = NULL;
    time(&t);
    transaccion.fecha = localtime(&t);
    transaccion.descripcion = "Ingreso manual";
    EscribirEnLogTrans(transaccion);
    EditarCsv(user);
    sem_post(semaforo);
    printf("Ingreso completado\n");
    return(0);
}
