#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para simular la creación de un usuario

#define FIFO_PATH "/tmp/mi_fifo_cerrar"
#define FIFO_PATH_B "/tmp/mi_fifo_inicio"

int main() {
    int fd_escritura;
    int fd_escritura_b;
    int nuevo_usuario_id;
    int antiguo_usuario_id;
    time_t t;
    int usr[]={1001,1001,1002,1001,1003,1002};  

    
    while ((fd_escritura_b = open(FIFO_PATH_B, O_WRONLY)) == -1) {
        perror("Banco: Error al abrir el FIFO para escritura. Intentando de nuevo...");
        sleep(1); // Esperar un poco antes de reintentar
    }
    // Intentar abrir el FIFO para escritura. Si no existe, el monitor aún no está listo.
    
    while ((fd_escritura = open(FIFO_PATH, O_WRONLY)) == -1) {
        perror("Banco: Error al abrir el FIFO para escritura. Intentando de nuevo...");
        sleep(1); // Esperar un poco antes de reintentar
    }

    printf("Banco: FIFO abierto para escritura.\n");

    // Simulación de eventos (creación de usuarios)
    srand((unsigned) time(&t)); // Inicializar el generador de números aleatorios

    for (int i = 0; i < 6; i++) {
        sleep(rand() % 5 + 1); // Simular un tiempo aleatorio entre eventos
        nuevo_usuario_id = usr[i]; // Generar un ID de usuario aleatorio

        printf("Banco: Detectado nuevo usuario con ID: %d. Enviando al monitor...\n", nuevo_usuario_id);
        if (write(fd_escritura_b, &nuevo_usuario_id, sizeof(int)) == -1) {
            perror("Banco: Error al escribir en el FIFO");
            break; // Salir del bucle si hay un error de escritura
        }
    }
    for (int i = 0; i < 6; i++) {
        sleep(rand() % 5 + 1); // Simular un tiempo aleatorio entre eventos
        antiguo_usuario_id= usr[i]; // Generar un ID de usuario aleatorio

        printf("Banco: Detectado nuevo log out con ID: %d. Enviando al monitor...\n", antiguo_usuario_id);
        if (write(fd_escritura, &antiguo_usuario_id, sizeof(int)) == -1) {
            perror("Banco: Error al escribir en el FIFO");
            break; // Salir del bucle si hay un error de escritura
        }
    }
    sleep(100000);
    close(fd_escritura);
    printf("Banco: Terminando.\n");

    return 0;
}
