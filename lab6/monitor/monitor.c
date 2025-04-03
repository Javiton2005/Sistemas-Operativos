#include "monitor.h"


// Estructuras para almacenar estadísticas
TRANSACCION **transacciones;
USER **users;

int fd_pipe[2]; // Pipe para enviar mensajes de anomalias al banco


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
    // Comprobar si alguna cuenta tiene saldo negativo
    for (int i = 0; i < Estadisticas.num_transacciones; i++) {
        if (transacciones[i]->cantidad < 0) {
            registrar_anomalia(ESTADO_FONDOS_INSUFICIENTES);
        }
    }
    return NULL;
}

// Detección de transacciones demasiado grandes
void *hilo_transacciones_grandes(void *arg) {     

    // Comprobar si hay transacciones con monto mayor a 1000
    for (int i = 0; i < Estadisticas.num_transacciones; i++) {
        if (transacciones[i]->cantidad > 1000.0) {
            registrar_anomalia(ESTADO_EXCEDE_LIMITE);
        }
    }
    return NULL;
}

// Detección de intentos de login fallidos
void *hilo_login_fallido(void *arg) {
        
    int intentos_previos = 0;

    

    // Comprobar si hay nuevos intentos de login fallidos
    if (intentos_previos > Config.limite_login) {
        registrar_anomalia(ESTADO_CONSTRASENA_INCORRECTA);
        
    }
    return NULL;
}

// Detección de muchas secuencias inusuales en poco tiempo (3 transacciones en menos de 1 minuto)
void *hilo_secuencia_inusual(void *arg) {

    // Verificar si hay múltiples transacciones para una misma cuenta en un corto período
    if (Estadisticas.num_transacciones < 3) return NULL;
    else if (Estadisticas.num_transacciones >= 3) {
        for (int i = 0; i < Estadisticas.usuarios; i++) {
            int id_cuenta_sospechosa = users[i]->id;
            int transacciones_rapidas = 0;
            time_t tiempo_base = time(NULL);
            
            for (int j = 0; j < Estadisticas.num_transacciones; j++) {
                if (transacciones[j]->ncuentao == id_cuenta_sospechosa) {
                    time_t tiempo_actual = time(NULL);  // Obtener el tiempo de la transacción actual

                    if ((tiempo_actual - tiempo_base) < 60000000) { // Si está dentro del último minuto
                        transacciones_rapidas++;
                        if (transacciones_rapidas >= 3) registrar_anomalia(ESTADO_SECUENCIA_INUSUAL);
                    } else {
                        // Reiniciar contador si la nueva transacción es después de 1 minuto
                        tiempo_base = tiempo_actual;
                        transacciones_rapidas = 1;
                    }
                }
            }
        }
    }  
    return NULL;
}

// Detección de usuarios que no existen
void *hilo_usuario_no_existe(void *arg) {
        
    // Verificar si hay transacciones para usuarios que no existen
    for (int i = 0; i < Estadisticas.num_transacciones; i++) {
        if (transacciones[i]->ncuentao == NULL) {
            registrar_anomalia(ESTADO_USUARIO_NO_EXISTE);
        }
    }
    return NULL;
}


// Función monitor principal
void monitor(int fd_alerta) {
    fd_pipe[1] = fd_alerta; // Pipe para enviar mensajes al banco

    transacciones = CrearListaTransacciones(Config.archivo_tranferencias);
    if (!transacciones) {
        printf("Error al crear la lista de transacciones.\n");
        return;
    }

    while (transacciones[Estadisticas.num_transacciones] != NULL) {
        Estadisticas.num_transacciones++;
    }

    users = CrearListaCuentas(Config.archivo_cuentas);
    if (!users) {
        printf("Error al crear la lista de cuentas.\n");
        return;
    }

    pthread_t hilo_fondos, hilo_transacciones_grandes, hilo_login, hilo_internacional, hilo_secuencia, hilo_no_existe;

    // Crear hilos para anomalías
    pthread_create(&hilo_fondos, NULL, hilo_fondos_insuficientes, NULL);
    pthread_create(&hilo_transacciones_grandes, NULL, hilo_transacciones_grandes, NULL);
    pthread_create(&hilo_login, NULL, hilo_login_fallido, NULL);
    pthread_create(&hilo_secuencia, NULL, hilo_secuencia_inusual, NULL);
    pthread_create(&hilo_no_existe, NULL, hilo_usuario_no_existe, NULL);

    // CODIGO PARA LEER TRANSACCIONES Y CUENTAS
    pthread_join(hilo_fondos, NULL);
    pthread_join(hilo_transacciones_grandes, NULL);
    pthread_join(hilo_login, NULL);
    pthread_join(hilo_secuencia, NULL);
    pthread_join(hilo_no_existe, NULL);
}

