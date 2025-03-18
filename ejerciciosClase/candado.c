#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Variable compartida entre hilos
int contador = 0;

// Definición del mutex (variable cerradura)
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// Función que ejecutarán los hilos
void* incrementar(void* arg) {
    int id = ((int) arg), i;
//    int i;
    
    for (i = 0; i < 5; i++) {
        // Adquirir el mutex (cerrar la cerradura)
        printf("Hilo %d: Intentando entrar a la sección crítica...\n", id);
        pthread_mutex_lock(&lock);
        
        // INICIO DE SECCIÓN CRÍTICA
        printf("Hilo %d: Dentro de la sección crítica\n", id);
        
        // Simulamos algún trabajo en la sección crítica
        int valor_actual = contador;
        printf("Hilo %d: Leyó contador = %d\n", id, valor_actual);
        
        // Simulamos una operación que toma tiempo
        sleep(1);
        
        // Actualizamos el contador
        contador = valor_actual + 1;
        printf("Hilo %d: Actualizó contador a %d\n", id, contador);
        
        // FIN DE SECCIÓN CRÍTICA
        
        // Liberar el mutex (abrir la cerradura)
        printf("Hilo %d: Saliendo de la sección crítica\n", id);
        pthread_mutex_unlock(&lock);
        
        // Hacemos algo fuera de la sección crítica
        printf("Hilo %d: Trabajando fuera de la sección crítica\n", id);
        sleep(rand() % 2);
    }
    
    free(arg);
  return NULL;
}

int main() {
    pthread_t hilo1, hilo2, hilo3;
    int *id1, *id2, *id3;
    
    // Asignar IDs a los hilos
    id1 = malloc(sizeof(int));
    id2 = malloc(sizeof(int));
    id3 = malloc(sizeof(int));
    
    *id1 = 1;
    *id2 = 2;
    *id3 = 3;
    
    // Crear los hilos
    pthread_create(&hilo1, NULL, incrementar, id1);
    pthread_create(&hilo2, NULL, incrementar, id2);
    pthread_create(&hilo3, NULL, incrementar, id3);
    
    // Esperar a que terminen los hilos
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);
    
    printf("Valor final del contador: %d\n", contador);
    
    // Destruir el mutex
    pthread_mutex_destroy(&lock);
    
    return 0;
}
