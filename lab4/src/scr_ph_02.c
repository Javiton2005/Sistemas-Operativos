//#include <bits/pthreadtypes.h>
#include <stdio.h>
//#include <unistd.h> añadido por probar el sleep
#include <stdlib.h>
#include <pthread.h>

#define MAX_LINE_LENGTH 256

FILE* file;

void* readAndPrintLines(void* arg) {
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("Hilo %ld: %s", pthread_self(), line);
    } 
    return NULL;
}

int main() {
    pthread_t *threads=malloc(sizeof(pthread_t)*10);

    // Abrir el fichero
    file = fopen("Retos.txt", "r");
    if (file == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // Crear los hilos
    if (pthread_create(&threads[0], NULL, &readAndPrintLines, NULL) != 0 ||
        pthread_create(&threads[1], NULL, &readAndPrintLines, NULL) != 0 ||
        pthread_create(&threads[2], NULL, &readAndPrintLines, NULL) != 0 ||
        pthread_create(&threads[3], NULL, &readAndPrintLines, NULL) != 0 ||
        pthread_create(&threads[4], NULL, &readAndPrintLines, NULL) != 0 ||
        pthread_create(&threads[5], NULL, &readAndPrintLines, NULL) != 0 ||
        pthread_create(&threads[6], NULL, &readAndPrintLines, NULL) != 0 ||
        pthread_create(&threads[7], NULL, &readAndPrintLines, NULL) != 0 ||
        pthread_create(&threads[8], NULL, &readAndPrintLines, NULL) != 0 ||
        pthread_create(&threads[9], NULL, &readAndPrintLines, NULL) != 0 ) {
        perror("pthread_create");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Esperar a que los hilos terminen
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
    pthread_join(threads[4], NULL);
    pthread_join(threads[5], NULL);
    pthread_join(threads[6], NULL);
    pthread_join(threads[7], NULL);
    pthread_join(threads[8], NULL);
    pthread_join(threads[9], NULL);
    // Limpieza
    fclose(file);

    return EXIT_SUCCESS;
}
