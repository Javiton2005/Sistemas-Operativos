#include "monitor.h"
#include <stdio.h>
#include <string.h>


// Estructuras para almacenar estadísticas
TRANSACCION **transacciones;
USER **users = NULL;

int fd_pipe[2]; // Pipe para enviar mensajes de anomalias al banco

// Mutex y variable de condicion para sincronización de hilos
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para proteger el acceso a la variable compartida
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // Variable de condición para esperar la señal de nuevo chequeo
int nueva_verificacion = 0; // Variable para indicar si hay un nuevo chequeo (tomara valores 0 o 1)

// Función para registrar anomalías en el log y mandar al banco
void registrar_anomalia(int codigo_anomalia) {
    char mensaje[50];
    sprintf(mensaje,"ANOMALÍA %d\n", codigo_anomalia);
    EscribirEnLog(mensaje);
    write(fd_pipe[1], mensaje, sizeof(mensaje)); // Enviar mensaje al banco
}

//------------------------------ FUNCIONES DE LOS HILOS PARA DETECTAR ANOMALÍAS ------------------------------

// Detección de fondos insuficientes
void *hilo_fondos_insuficientes(void *arg) {       
    while(1){
        pthread_mutex_lock(&mutex);
        while (!nueva_verificacion) {
            pthread_cond_wait(&cond, &mutex); // Esperar señal de nuevo chequeo
        }
        pthread_mutex_unlock(&mutex);

        // Comprobar si alguna cuenta tiene saldo negativo
        for (int i = 0; i < Estadisticas.num_transacciones; i++) {
            if (transacciones[i]->cantidad < 0) {
                registrar_anomalia(ESTADO_FONDOS_INSUFICIENTES);
            }
        }

        sleep(1); // Simular tiempo de procesamiento
    }
    return NULL;
}

// Detección de transacciones demasiado grandes
void *hilo_transacciones_grandes(void *arg) {     
    while(1){
        pthread_mutex_lock(&mutex);
        while (!nueva_verificacion) {
            pthread_cond_wait(&cond, &mutex); // Esperar señal de nuevo chequeo
        }
        pthread_mutex_unlock(&mutex);

        // Comprobar si hay transacciones con monto mayor a 1000
        for (int i = 0; i < Estadisticas.num_transacciones; i++) {
            if (transacciones[i]->cantidad > 1000.0) {
                registrar_anomalia(ESTADO_EXCEDE_LIMITE);
            }
        }

        sleep(1); // Simular tiempo de procesamiento
    }
    return NULL;
}

// Detección de muchas secuencias inusuales en poco tiempo (3 transacciones en menos de 1 minuto)
void *hilo_secuencia_inusual(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (!nueva_verificacion) {
            pthread_cond_wait(&cond, &mutex); // Espera hasta que lo despierten
        }
        pthread_mutex_unlock(&mutex);

        if (Estadisticas.num_transacciones >= 3) {
            for (int i = 0; i < Estadisticas.usuarios; i++) {
                int transacciones_rapidas = 0;
                time_t tiempo_base = 0;

                for (int j = 0; j < Estadisticas.num_transacciones; j++) {
                    if (strcmp(transacciones[j]->ncuentao, users[i]->ncuenta) == 0) {
                        struct tm fecha_tm = transacciones[j]->fecha;
                        time_t tiempo_actual = mktime(&fecha_tm); // Convertir a time_t

                        if (tiempo_base == 0) {
                            tiempo_base = tiempo_actual;
                            transacciones_rapidas = 1;
                        } else {
                            double diferencia = difftime(tiempo_actual, tiempo_base);

                            if (diferencia < 60) { // Menos de un minuto
                                transacciones_rapidas++;
                                if (transacciones_rapidas >= 3) {
                                    registrar_anomalia(ESTADO_SECUENCIA_INUSUAL);
                                    break; // Salir si ya se detectó para este usuario
                                }
                            } else {
                                // Reiniciar ventana de tiempo
                                tiempo_base = tiempo_actual;
                                transacciones_rapidas = 1;
                            }
                        }
                    }
                }
            }
        }

        sleep(1); // Simular tiempo de procesamiento
    }

    return NULL;
}

// Detección de usuarios que no existen
void *hilo_usuario_no_existe(void *arg) {
    while(1){
        pthread_mutex_lock(&mutex);
        while (!nueva_verificacion) {
            pthread_cond_wait(&cond, &mutex); // Esperar señal de nuevo chequeo
        }
        pthread_mutex_unlock(&mutex);

        // Verificar si hay transacciones para usuarios que no existen
        for (int i = 0; i < Estadisticas.num_transacciones; i++) {
            if (transacciones[i]->ncuentao == NULL) {
                registrar_anomalia(ESTADO_USUARIO_NO_EXISTE);
            }
        }

        sleep(1); // Simular tiempo de procesamiento
    }
    return NULL;
}

//------------------------------ MONITOR PRINCIPAL ------------------------------

// Función para notificar a los hilos de revisar posibles anomalias
void notificar_hilos() {
    pthread_mutex_lock(&mutex);
    
    Estadisticas.num_transacciones = 0;

    transacciones = CrearListaTransacciones(Config.archivo_tranferencias);
    if (!transacciones) {
        printf("Error al crear la lista de transacciones.\n");
        return;
    }

    while (transacciones[Estadisticas.num_transacciones] != NULL) {
        Estadisticas.num_transacciones++;
    }

    users = CrearListaUsuarios(Config.archivo_cuentas);
    if (!users) {
        printf("Error al crear la lista de cuentas.\n");
        return;
    }
    nueva_verificacion = 1;
    pthread_cond_broadcast(&cond); // Despierta a todos los hilos bloqueados
    pthread_mutex_unlock(&mutex);
}

// Función monitor principal
void monitor(int fd_alerta) {
    fd_pipe[1] = fd_alerta; // Pipe para enviar mensajes al banco

    pthread_t hilo_fondos, hilo_transacciones, hilo_internacional, hilo_secuencia, hilo_no_existe;

    // Crear hilos para anomalías
    pthread_create(&hilo_fondos, NULL, hilo_fondos_insuficientes, NULL);
    pthread_create(&hilo_transacciones, NULL, hilo_transacciones_grandes, NULL);
    pthread_create(&hilo_secuencia, NULL, hilo_secuencia_inusual, NULL);
    pthread_create(&hilo_no_existe, NULL, hilo_usuario_no_existe, NULL);

    // Los hilos corren indefinidamente esperando a señales

    while (1) {
        notificar_hilos(); // Notificar a los hilos para revisar posibles anomalías

        // Resetear la variable de chequeo para siguientes verificaciones
        pthread_mutex_lock(&mutex);
        nueva_verificacion = 0;
        pthread_mutex_unlock(&mutex);

        sleep(10); // Esperar 10 segundos antes de la siguiente verificación
    }

    // CODIGO PARA LEER TRANSACCIONES Y CUENTAS
    /*pthread_join(hilo_fondos, NULL);
    pthread_join(hilo_transacciones_grandes, NULL);
    pthread_join(hilo_secuencia, NULL);
    pthread_join(hilo_no_existe, NULL);*/
}
