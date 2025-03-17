#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LIMITE_TRANSFERENCIA 1000.0

int mainmonitor() {
    double cantidad;
    int respuesta;
    
    // El monitor recibe datos en stdin y envía respuestas por stdout
    printf("Monitor: Iniciado. Esperando transacciones...\n");
    printf("Monitor: Límite de transferencia establecido en %.2f\n", LIMITE_TRANSFERENCIA);
    
    while (1) {
        // Leer cantidad enviada por el banco
        ssize_t bytes_leidos = read(STDIN_FILENO, &cantidad, sizeof(double));
        
        if (bytes_leidos > 0) {
            printf("Monitor: Recibida solicitud para transferir %.2f\n", cantidad);
            
            // Verificar si la cantidad supera el límite
            if (cantidad > LIMITE_TRANSFERENCIA) {
                printf("Monitor: ¡ALERTA! Cantidad superior al límite permitido.\n");
                respuesta = 1; // Rechazada
            } else {
                printf("Monitor: Cantidad dentro de límites aceptables.\n");
                respuesta = 0; // Aprobada
            }
            
            // Enviar respuesta al banco
            write(STDOUT_FILENO, &respuesta, sizeof(int));
            printf("Monitor: Respuesta enviada: %s\n", 
                   respuesta == 0 ? "APROBADA" : "RECHAZADA");
        } else if (bytes_leidos == 0) {
            // El otro extremo del pipe se cerró
            printf("Monitor: Conexión con el banco cerrada. Saliendo...\n");
            break;
        }
    }
    
    return 0;
}
