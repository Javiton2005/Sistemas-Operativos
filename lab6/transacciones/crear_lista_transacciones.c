#include "transacciones.h"
#include <stdio.h>
#include <stdlib.h>

TRANSACCION **CrearListaTransacciones(char *fichero) {
    if (fichero == NULL) {
        printf("No se ha dado un fichero\n");
        return NULL;
    }

    TRANSACCION **listaTransacciones = NULL;
    char *linea = NULL;
    FILE *archivo = fopen(fichero, "r");
    if (!archivo) {
        printf("Error al abrir el archivo de transacciones.\n");
        return NULL;
    }

    char caracter;
    int transacciones = 0;
    int caracteres = 0;

    while ((caracter = fgetc(archivo)) != '\n' && caracter != EOF); // Saltar primera línea

    while (1) {
        caracter = fgetc(archivo);
        linea = realloc(linea, caracteres + 1);
        linea[caracteres] = caracter;
        caracteres++;

        if (caracter == '\n' || caracter == EOF) {
            linea[caracteres] = '\0';
            TRANSACCION *transaccion = crearTransaccion(linea, transacciones);
            
            listaTransacciones = realloc(listaTransacciones, (transacciones + 1) * sizeof(TRANSACCION *));
            listaTransacciones[transacciones] = transaccion;
            transacciones++;
            
            caracteres = 0;
        }
        if (caracter == EOF)
            break;
    }

    free(linea);
    fclose(archivo);
    
    return listaTransacciones;
}

