#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <threads.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define LIMITE_TRANSFERENCIA 1000.0

#define ESTADO_APROBADA 0
#define ESTADO_EXCEDE_LIMITE 1

int MainMonitor(){

  int banco_a_monitor[2]; // Pipe para enviar datos del banco al monitor
  int monitor_a_banco[2]; // Pipe para enviar datos del monitor al banco
  pid_t pid;

  // Crear los pipes
  if (pipe(banco_a_monitor) == -1 || pipe(monitor_a_banco) == -1) {
      perror("Error al crear los pipes");
      exit(EXIT_FAILURE);
  }

  // Crear un proceso hijo (monitor)
  pid = fork();

  if (pid < 0) {

    perror("Error en fork");
    exit(EXIT_FAILURE);

  } else if (pid == 0) { // Hijo (MONITOR)

    double cantidad;
    int respuesta;

    close(banco_a_monitor[1]); // Cierra escritura en banco_a_monitor
    close(monitor_a_banco[0]); // Cierra lectura en monitor_a_banco
        
    while (1) {
      // Leer cantidad enviada por el banco
      ssize_t bytes_leidos = read(banco_a_monitor[0], &cantidad, sizeof(double));
      
      if (bytes_leidos > 0) {          
          // Verificar si la cantidad supera el límite
          if (cantidad > LIMITE_TRANSFERENCIA) {
              respuesta = 1; // Rechazada
          } else {
              respuesta = 0; // Aprobada
          }
          
          // Enviar respuesta al banco usando el pipe de monitor a banco
          write(monitor_a_banco[1], &respuesta, sizeof(int));
      } else if (bytes_leidos == 0) {
          // El otro extremo del pipe se cerró
          break;
      }
    }
    // Cerrar pipe
    close(banco_a_monitor[0]);
    close(monitor_a_banco[1]);
    exit(EXIT_SUCCESS);

  } else { //Padre (BANCO)

    double cantidad;
    int respuesta;
    
    // Cerrar extremos no necesarios
    close(banco_a_monitor[0]); // Cierra lectura en banco_a_monitor
    close(monitor_a_banco[1]); // Cierra escritura en monitor_a_banco
    
    printf("Banco: Conectado con el monitor (PID: %d).\n", pid);
    
    while (1) {
        // Solicitar cantidad al usuario
        printf("\nBanco: Ingrese cantidad a transferir (0 para salir): ");
        scanf("%lf", &cantidad);
        
        if (cantidad == 0) {
            break;
        }
        
        // Enviar cantidad al monitor
        write(banco_a_monitor[1], &cantidad, sizeof(double));
        printf("\nBanco: Cantidad %.2f enviada al monitor para verificación.\n", cantidad);
        
        // Recibir respuesta del monitor
        read(monitor_a_banco[0], &respuesta, sizeof(int));
        
        if (respuesta == 0) {
            printf("Banco: Transacción APROBADA por el monitor.\n");
            printf("Banco: %.2f transferidos al usuario...\n", cantidad);
        } else if (respuesta == 1) {
            printf("Banco: Transacción RECHAZADA por el monitor. Cantidad demasiado alta.\n");
            printf("Banco: Limite de transferencia es %.2lf\n", LIMITE_TRANSFERENCIA);
        }
    }
    
    // Cerrar pipes
    close(banco_a_monitor[1]);
    close(monitor_a_banco[0]);
    
    // Esperar a que el proceso hijo termine
    wait(NULL);
    
    printf("Banco: Proceso terminado.\n");
  }
  return 0; 
}
