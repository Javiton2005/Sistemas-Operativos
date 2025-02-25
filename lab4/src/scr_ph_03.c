//#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_LINE_LENGTH 256
#define MAX_NUM_THREADS 4
FILE* file;

void* readAndPrintLines(void* arg) {
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("Hilo %ld: %s", pthread_self(), line);
    }

    return NULL;
}

int main() {
    pthread_t threads[MAX_NUM_THREADS];
    int thread_out, i;
  //pthread_t thread1, thread2, thread3, thread4;

    // Abrir el fichero
    file = fopen("archivo.txt", "r");
    if (file == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }
    
    for(i=0; i<MAX_NUM_THREADS;i++){
      thread_out=pthread_create(&threads[i], NULL, &readAndPrintLines, NULL);
      if(thread_out != 0){
        
        for (int j=0; j<i; i++){
          pthread_cancel(threads[j]);
        }
        perror("pthread_create");
        fclose(file);
        return EXIT_FAILURE;
      }
    }
    // Crear los hilos

    // Esperar a que los hilos terminen
    for(i=0; i<MAX_NUM_THREADS;i++){
      pthread_join(threads[i],NULL);
    }

    // Limpieza
    fclose(file);

    return EXIT_SUCCESS;
}
