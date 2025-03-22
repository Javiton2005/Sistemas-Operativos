#include "comun/comun.h"
#define ESTADO_APROBADA 0
#define ESTADO_FONDOS_INSUFICIENTES 1
#define ESTADO_EXCEDE_LIMITE 2
#define ESTADO_CONSTRASEÑA_INCORRECTA 3
#define ESTADO_TRANSACCION_INTERNACIONAL 4
#define ESTADO_SECUENCIA_INUSUAL 5
#define ESTADO_USUARIO_DESTINO_NO_EXISTE 6

#define LIMITE_TRANSFERENCIA 1000.0
#define LIMITE_INTENTOS_LOGIN 3

// Función monitor principal
int monitor(int codigo, void* datos, void* datos2) {
    
    double cantidad;
    int respuesta;
    
    // Crear hilos para anomalías
    pthread_t hilo_fondos, hilo_transacciones_grandes, hilo_login, hilo_internacional, hilo_secuencia, hilo_no_existe;
    
    pthread_create(&hilo_fondos, NULL, hilo_fondos_insuficientes, NULL);
    pthread_create(&hilo_transacciones_grandes, NULL, hilo_transacciones_grandes, NULL);
    pthread_create(&hilo_login, NULL, hilo_login_fallido, NULL);
    pthread_create(&hilo_internacional, NULL, hilo_transacciones_internacionales, NULL);
    pthread_create(&hilo_secuencia, NULL, hilo_secuencia_inusual, NULL);
    pthread_create(&hilo_no_existe, NULL, hilo_usuario_no_existe, NULL);

    // CODIGO PARA LEER TRANSACCIONES Y CUENTAS
    
    pthread_join(hilo_fondos, NULL);
    pthread_join(hilo_transacciones_grandes, NULL);
    pthread_join(hilo_login, NULL);
    pthread_join(hilo_internacional, NULL);
    pthread_join(hilo_secuencia, NULL);
    pthread_join(hilo_no_existe, NULL);
        
    return 0;
}

// Función para registrar anomalías en el log
void registrar_anomalia(int codigo_anomalia) {
    
    char tiempo_str[20];
    time_t tiempo = time(NULL);
    struct tm *tiempo_info = localtime(&tiempo);
    strftime(tiempo_str, sizeof(strftime), "%Y-%m-%d %H:%M:%S", tiempo_info);

    printf("[%s] ANOMALÍA %d\n", tiempo_str, codigo_anomalia);
    sleep(5);

    if (codigo_anomalia == ESTADO_APROBADA) {
        return;
    }

    char mensaje_anomalia[50];    
    sprintf(mensaje_anomalia, "[%s] ANOMALÍA %d\n", tiempo_str, codigo_anomalia);

    //ENVIAR MENSAJE_ANOMALIA AL BANCO

    return;
}

//------------------------------ FUNCIONES DE LOS HILOS PARA DETECTAR ANOMALÍAS ------------------------------

// Detección de fondos insuficientes
void *hilo_fondos_insuficientes(void *arg) {
        
    // Comprobar si alguna cuenta tiene saldo negativo
    for (int i = 0; i < monitor.num_cuentas; i++) {
        if (monitor.cuentas[i].saldo < 0) {
            registrar_anomalia(ESTADO_FONDOS_INSUFICIENTES);
        }
    }
    return NULL;
}

// Detección de transacciones demasiado grandes
void *hilo_transacciones_grandes(void *arg) {     

    // Comprobar si hay transacciones con monto mayor a 1000
    for (int i = 0; i < monitor.num_transacciones; i++) {
        if (monitor.transacciones[i].monto > 1000.0) {
            registrar_anomalia(ESTADO_EXCEDE_LIMITE);
        }
    }
    return NULL;
}

// Detección de intentos de login fallidos
void *hilo_login_fallido(void *arg) {
        
    int intentos_previos = 0;

    // Comprobar si hay nuevos intentos de login fallidos
    if (monitor.num_intentos_login >= LIMITE_INTENTOS_LOGIN) {
        registrar_anomalia(ESTADO_CONSTRASEÑA_INCORRECTA);
        intentos_previos = monitor.num_intentos_login;
    }
    return NULL;
}

// Detección de transacciones internacionales
void *hilo_transacciones_internacionales(void *arg) {
        
    // Comprobar si hay transacciones internacionales
    for (int i = 0; i < monitor.num_transacciones; i++) {
        if (monitor.transacciones[i].pais != monitor.usuario.pais) {
            registrar_anomalia(ESTADO_TRANSACCION_INTERNACIONAL);
        }
    }
    return NULL;
}

// Detección de muchas secuencias inusuales en poco tiempo (3 transacciones en menos de 1 minuto)
void *hilo_secuencia_inusual(void *arg) {
        
    // Verificar si hay múltiples transacciones para una misma cuenta en un corto período
    if (monitor.num_transacciones >= 3) {
        for (int i = 0; i < monitor.num_cuentas; i++) {
            int id_cuenta = monitor.cuentas[i].id_cuenta;
            int transacciones_rapidas = 0;
            time_t tiempo_base = 0;
            
            for (int j = 0; j < monitor.num_transacciones; j++) {
                if (monitor.transacciones[j].id_cuenta == id_cuenta) {
                    if (tiempo_base == 0) {
                        tiempo_base = monitor.transacciones[j].timestamp;
                        transacciones_rapidas = 1;
                    } else if (monitor.transacciones[j].timestamp - tiempo_base < 60) { // 60 segundos
                        transacciones_rapidas++;
                        if (transacciones_rapidas >= 3) {
                            registrar_anomalia(ANOMALIA_SECUENCIA_INUSUAL);
                            break;
                        }
                    } else {
                        tiempo_base = monitor.transacciones[j].timestamp;
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
    for (int i = 0; i < monitor.num_transacciones; i++) {
        if (monitor.transacciones[i].id_usuario_destino == -1) {
            registrar_anomalia(ESTADO_USUARIO_DESTINO_NO_EXISTE);
        }
    }
    return NULL;
}
