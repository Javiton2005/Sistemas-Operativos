#include "comun/comun.h"
#include "usuarios/usuarios.h"
#include "transacciones/transacciones.h"
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#define TIMEOUT_SEC 1

volatile bool detener_hilos_logs = false;
int *listaUsuarios;
struct tm **ultimasTransacciones;
long *posiciones;
int nusers;
struct timeval timeout;
fd_set readfds;
pthread_mutex_t mutex;
// Función para registrar anomalías en el log y mandar al banco
void registrar_anomalia(int codigo_anomalia) {
    char mensaje[50];
    sprintf(mensaje,"ANOMALÍA %d\n", codigo_anomalia);
    EscribirEnLog(mensaje);
    printf("ANOMALÍA n:%d\n", codigo_anomalia);
}

//------------------------------ FUNCIONES DE LOS HILOS PARA DETECTAR ANOMALÍAS ------------------------------

void liberarMemoria(){
  
  free(listaUsuarios);
  free(posiciones); 
  for (int i =0; i<nusers;i++) {
    free(ultimasTransacciones[i]);
  }
  return;
}
// Detección de transacciones demasiado grandes
void *hilo_transacciones_grandes(void *arg) {
  FILE *archivo;
  char nombre_archivo[50];
  char linea[256];
  for(int i=0; i<nusers;i++){
    if(listaUsuarios[i]==0)
      continue;

    pthread_mutex_lock(&mutex);
    sprintf(nombre_archivo, "./ficheros/%d/transacciones.log", 1001 + i);
    archivo = fopen(nombre_archivo, "r");
    if(archivo==NULL){
      printf("No se ha podido abrir el fichero %s\n",nombre_archivo);
      continue;
    }
    else {
      fseek(archivo, posiciones[i] , SEEK_SET);

      while (fgets(linea, 256, archivo)){
        TRANSACCION *transaccion = crearTransaccion(linea);
        if(transaccion->cantidad>Config.limite_transferencia && transaccion->cantidad>Config.limite_retiro)
          registrar_anomalia(ESTADO_EXCEDE_LIMITE); 
        ultimasTransacciones[i][0]=ultimasTransacciones[i][1];
        ultimasTransacciones[i][1]=ultimasTransacciones[i][2];
        ultimasTransacciones[i][2]=transaccion->fecha;
        
        free(transaccion);
      }
      posiciones[i]=ftell(archivo);
    }
    fclose(archivo);
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

// Detección de muchas secuencias inusuales en poco tiempo (3 transacciones en menos de 1 minuto)

bool es_fecha_valida(struct tm *fecha) {
    return !(fecha->tm_year == 0 && fecha->tm_mon == 0 && fecha->tm_mday == 0);
}

void *hilo_secuencia_inusual(void *arg) {
  for (int i = 0; i < nusers; i++) {

    if (!es_fecha_valida(&ultimasTransacciones[i][0]) ||
        !es_fecha_valida(&ultimasTransacciones[i][2])) {
        continue; // No hay 3 fechas válidas aún
    }

    time_t t1 = mktime(&ultimasTransacciones[i][0]);
    time_t t3 = mktime(&ultimasTransacciones[i][2]);  // tercera transacción

    double diferencia = difftime(t3, t1);  // en segundos

    if (diferencia < 60.0) {
      // "Vaciar" la lista sin liberar memoria
      for (int j = 0; j < 3; j++) {
        memset(&ultimasTransacciones[i][j], 0, sizeof(struct tm));
      }
      registrar_anomalia(ESTADO_SECUENCIA_INUSUAL);
    }
  }
  return NULL;
}

void *hilo_comprobar_login(void *arg){

  int *fd_lectura_inicio=(int *) arg;
  int numero_user;
  int *listaUsrs;

  while (!detener_hilos_logs) {
    FD_ZERO(&readfds);  // Limpia antes de volver a usar
    FD_SET(*fd_lectura_inicio, &readfds);

    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;
    int retval = select(*fd_lectura_inicio + 1, &readfds, NULL, NULL, &timeout);
    if (retval == -1) {
      perror("Monitor: Error en select()");
      break;
    } else if (retval > 0) {
      // Hay datos disponibles para leer en el FIFO
      if (FD_ISSET(*fd_lectura_inicio, &readfds)) {
        ssize_t bytes_leidos = read(*fd_lectura_inicio, &numero_user, sizeof(int));
        if (bytes_leidos == sizeof(int)) {
          pthread_mutex_lock(&mutex);
          int index = numero_user - 1001;
          if (index >= nusers) {
            int nuevo_tam = index + 1;
            int *nuevo = realloc(listaUsuarios, nuevo_tam * sizeof(int));
            if (!nuevo) {
                perror("Error en realloc");
                break;
            }
            posiciones = realloc(posiciones, nuevo_tam * sizeof(long));

            ultimasTransacciones = realloc(ultimasTransacciones, nuevo_tam*sizeof(struct tm*));
            
            if (!posiciones && ultimasTransacciones) {
                perror("Error en realloc");
                break;
            }
            // Inicializa nuevos elementos a 0
            for (int i = nusers; i < nuevo_tam; i++) {
              
              ultimasTransacciones[i] = malloc(3 * sizeof(struct tm));
              posiciones[i]=0;
              nuevo[i] = 0;
            }
            char nombre_archivo[50];
            sprintf(nombre_archivo, "./ficheros/%d/config.conf", numero_user);
            FILE *archivo = fopen(nombre_archivo, "rb");
            if(!archivo){
              perror("error al abrir el archivo");
              liberarMemoria();
            }
            fread(nombre_archivo, sizeof(char), 50, archivo);
            posiciones[index]=atoi(nombre_archivo);
            printf("%ld\n",posiciones[index]);
            listaUsuarios = nuevo;
            fclose(archivo);
            nusers = nuevo_tam;

          }
          listaUsuarios[index]++;
          pthread_mutex_unlock(&mutex);
          printf("Usuario con id %d ha hecho log in %d veces\n", numero_user, listaUsuarios[index]);
        } else if (bytes_leidos == -1) {
          if (errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("Monitor: Error al leer del FIFO\n");
            break;
          }
        } else if (bytes_leidos == 0) {
          detener_hilos_logs=1;
          break;
        }
      }
    }
  }

  return NULL;
}


void *hilo_comprobar_logout(void *arg){
  int *fd_lectura_cerrar=(int *) arg;
  int numero_user;
  int *listaUsrs;

  while (!detener_hilos_logs) {
    FD_ZERO(&readfds);  // Limpia antes de volver a usar
    FD_SET(*fd_lectura_cerrar, &readfds);

    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;
    int retval = select(*fd_lectura_cerrar + 1, &readfds, NULL, NULL, &timeout);
    if (retval == -1) {
      perror("Monitor: Error en select()");
      break;
    } else if (retval > 0) {
      // Hay datos disponibles para leer en el FIFO
      if (FD_ISSET(*fd_lectura_cerrar, &readfds)) {
        ssize_t bytes_leidos = read(*fd_lectura_cerrar, &numero_user, sizeof(int));
        if (bytes_leidos == sizeof(int)) {
          pthread_mutex_lock(&mutex);
          int index = numero_user - 1001;
          listaUsuarios[index]--;
          char nombre_archivo[50];
          sprintf(nombre_archivo, "./ficheros/%d/config.conf", numero_user);
          FILE *archivo = fopen(nombre_archivo, "wb");
          if(!archivo){
            perror("error al abrir el archivo");
            liberarMemoria();
          }
          printf("Posicion del usuario es: %ld\n",posiciones[index]);
          fprintf(archivo, "%ld", posiciones[index]);
          fclose(archivo);
          pthread_mutex_unlock(&mutex);
          printf("Usuario con id %d se fue quedan %d veces\n", numero_user, listaUsuarios[index]);
        } else if (bytes_leidos == -1) {
          if (errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("Monitor: Error al leer del FIFO\n");
            break;
          }
        }
      }
    }
  }

  return NULL;
}


void hilos(pthread_t *hilo_transacciones,  pthread_t *hilo_secuencia){
  
  // Crear hilos para anomalías
  pthread_create(hilo_transacciones, NULL, hilo_transacciones_grandes, NULL);
  pthread_create(hilo_secuencia, NULL, hilo_secuencia_inusual, NULL);

  // CODIGO PARA LEER TRANSACCIONES Y CUENTAS
  pthread_join(*hilo_transacciones, NULL);
  pthread_join(*hilo_secuencia, NULL);
}
//------------------------------ MONITOR PRINCIPAL ------------------------------

// Función monitor principal

int main(int argc, char *argv[]) {

  InitGlobal();
  nusers=0;
  pthread_mutex_init(&mutex, NULL);
  listaUsuarios=calloc(1,sizeof(int));
  ultimasTransacciones=calloc(1, sizeof(struct tm*));
  pthread_t hilo_transacciones, hilo_secuencia, hilo_login,hilo_cerrar;
  
  int fd_lectura_cerrar;
  int fd_lectura_inicio;

  int id_usuario_recibido = -1; // Valor inicial para indicar que no se ha recibido nada aún
  int numero_user;

  // Crear el FIFO si no existe
  if (mkfifo(FIFO_INICIO, 0666) == -1) {
      if (errno != EEXIST) {
          perror("Error al crear el FIFO");
          return 1;
      }
      printf("Monitor: El FIFO INICIO ya existía.\n");
  } else {
      printf("Monitor: FIFO INICIO creado exitosamente.\n");
  }

  // Abrir el FIFO para lectura en modo no bloqueante (opcional, pero útil para select)
  fd_lectura_inicio = open(FIFO_INICIO, O_RDONLY | O_NONBLOCK);
  if (fd_lectura_inicio == -1) {
      perror("Monitor: Error al abrir el FIFO INICIO para lectura");
      return 1;
  }

  // Crear el FIFO si no existe
  if (mkfifo(FIFO_CERRAR, 0666) == -1) {
      if (errno != EEXIST) {
          perror("Error al crear el FIFO");
          return 1;
      }
      printf("Monitor: El FIFO CERRAR ya existía.\n");
  } else {
      printf("Monitor: FIFO CERRAR creado exitosamente.\n");
  }

  // Abrir el FIFO para lectura en modo no bloqueante (opcional, pero útil para select)
  fd_lectura_cerrar = open(FIFO_CERRAR, O_RDONLY | O_NONBLOCK);
  if (fd_lectura_cerrar == -1) {
      perror("Monitor: Error al abrir el FIFO CERRAR para lectura");
      return 1;
  }
  
  pthread_create(&hilo_login, NULL, hilo_comprobar_login, &fd_lectura_inicio);
  pthread_create(&hilo_cerrar, NULL, hilo_comprobar_logout, &fd_lectura_cerrar);

  while (!detener_hilos_logs) {
    hilos(&hilo_transacciones, &hilo_secuencia);
  }
  
  pthread_join(hilo_login, NULL);
  pthread_join(hilo_cerrar, NULL);
  

  return 0;
}
