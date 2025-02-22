#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void leerArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    char linea[100]; // Asumiendo que cada línea tiene menos de 100 caracteres
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("PID %d leyendo: %s", getpid(), linea);
    }

    fclose(archivo);
}

int main() {
    const char *nombreArchivo = "archivo.txt";

    for (int i = 0; i < 3; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork falló");
            exit(1);
        }

        if (pid == 0) { // Proceso hijo
            leerArchivo(nombreArchivo);
            exit(0); // Finaliza el proceso hijo
        }
    }
    // El proceso padre también lee el archivo
    leerArchivo(nombreArchivo);
    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < 3; ++i) {
        wait(NULL);
    }
    return 0;
}
