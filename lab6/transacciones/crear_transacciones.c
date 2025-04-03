#include "transacciones.h"

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
                transaccion->cantidad = atoi(palabra);
                break;
            case 1:
                transaccion->ncuentas = palabra;
                break;
            case 2:
                transaccion->ncuentao = palabra;
                break;
            case 3:
                transaccion->fecha = palabra;
                break;
            case 4:
                transaccion->descripcion = palabra;
                break;
        }
        indice++;
    }

    return transaccion;
}

