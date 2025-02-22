#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void leerYEscribirArchivo(const char *nombreArchivoEntrada, const char *nombreArchivoSalida) {
    FILE *archivoEntrada = fopen(nombreArchivoEntrada, "r");
    if (archivoEntrada == NULL) {
        perror("Error al abrir el archivo de entrada");
        exit(1);
    }

    FILE *archivoSalida = fopen(nombreArchivoSalida, "w");
    if (archivoSalida == NULL) {
        perror("Error al abrir el archivo de salida");
        exit(1);
    }

    char linea[100]; // Asumiendo que cada línea tiene menos de 100 caracteres
    while (fgets(linea, sizeof(linea), archivoEntrada) != NULL) {
        fprintf(archivoSalida, "PID %d leyendo: %s", getpid(), linea);
    }

    fclose(archivoEntrada);
    fclose(archivoSalida);
}

int main() {
    const char *nombreArchivoEntrada = "archivo.txt";
    const char *nombreArchivoSalida = "archivo_salida.txt";

    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork falló");
            exit(1);
        }

        if (pid == 0) { // Proceso hijo
            leerYEscribirArchivo(nombreArchivoEntrada, nombreArchivoSalida);
            exit(0); // Finaliza el proceso hijo
        }
    }

    // El proceso padre también lee y escribe en los archivos
    leerYEscribirArchivo(nombreArchivoEntrada, nombreArchivoSalida);

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < 3; ++i) {
        wait(NULL);
    }

    return 0;
}

