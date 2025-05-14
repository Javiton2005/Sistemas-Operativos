#include "transacciones.h"
// Función para crear una transacción a partir de una línea del CSV
TRANSACCION *crearTransaccion(char *linea) {
    
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
              // Extraer día, mes, año, hora, minutos y segundos con sscanf
              if (sscanf(palabra, "%d-%d-%d %d:%d:%d",
                       &transaccion->fecha.tm_mday,  // Día
                       &transaccion->fecha.tm_mon,   // Mes
                       &transaccion->fecha.tm_year,  // Año
                       &transaccion->fecha.tm_hour,  // Hora
                       &transaccion->fecha.tm_min,   // Minuto
                       &transaccion->fecha.tm_sec) != 6) { // Segundo
                perror("Error al convertir la fecha\n");
                exit(-1);
            }
              break;            
            case 4:
                transaccion->descripcion = palabra;
                break;
        }
        indice++;
    }

    return transaccion;
}
