#include "transacciones.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Función para crear una transacción a partir de una línea del CSV
TRANSACCION *crearTransaccion(char *linea, int nLinea) {
    
    TRANSACCION *transaccion = malloc(sizeof(TRANSACCION));
    
    int indice = 0;
    char *output;
    while ((output = strsep(&linea, ";")) != NULL) {
        char *palabra = strdup(output);
        if (*palabra == '\0')
            palabra = "N/A";
        
        switch (indice) {
            case 0:
                transaccion->usuario = palabra;
                break;
            case 1:
                transaccion->accion = palabra;  // "retiro", "ingreso", etc.
                break;
            case 2:
                transaccion->monto = atoi(palabra);
                break;
            case 3:
                transaccion->saldo = atoi(palabra);
                break;
            case 4:
                transaccion->timestamp = atol(palabra);  // Guardamos timestamp en formato numérico
                break;
            case 5:
                transaccion->linea = nLinea;
                break;
        }
        indice++;
    }

    return transaccion;
}

