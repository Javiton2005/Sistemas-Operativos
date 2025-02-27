#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_LINES 1024  // Máximo número de líneas que esperamos leer

// Esta es la función que el hilo ejecutará
// gcc -o hilo_programa programa.c -lpthread

typedef struct {
    char** lines;  // Array de líneas leídas del fichero
    int num_lines; // Número de líneas leídas
} ThreadData;

void* printLines(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    for (int i = 0; i < data->num_lines; i++) {
        printf("Hilo %ld: %s\n", pthread_self(), data->lines[i]);
        // Asumiendo que las líneas terminan con '\n'
    }

    return NULL;
}

int main() {
    FILE* file;
    pthread_t thread1, thread2, thread3, thread4;
    char* lines[MAX_LINES];
    int count = 0;
    ThreadData data1, data2, data3, data4;
    int c, max=0, contador=0, cuarto;
    char *linea;

    file = fopen("archivo.txt", "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    
    
    while ((c=fgetc(file))!=EOF){
      if(c=='\n'){
        if(contador>max){
          max=contador;
        }
        count++;
        contador=0;
      }
      contador++;
    }
    rewind(file);
    contador=0;
    linea = malloc(sizeof(char)*max);

    while (fgets(linea, max, file)){
      lines[contador]=strdup(linea);
      contador++;
    }
    fclose(file);
    

    cuarto = count/4;
    // Dividir las líneas entre los dos hilos
    data1.lines = lines;
    data1.num_lines = cuarto;
    data2.lines = &lines[count - cuarto];
    data2.num_lines = cuarto;
    data3.lines = &lines[count - cuarto*2];
    data3.num_lines = cuarto;
    data4.lines = &lines[count - cuarto*3];
    data4.num_lines = cuarto;

    // Crear los hilos
    pthread_create(&thread1, NULL, printLines, &data1);
    pthread_create(&thread2, NULL, printLines, &data2);
    pthread_create(&thread3, NULL, printLines, &data3);
    pthread_create(&thread4, NULL, printLines, &data4);

    // Esperar a que los hilos terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return EXIT_SUCCESS;
}

