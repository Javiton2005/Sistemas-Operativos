#include "comun/comun.h"
#include "usuarios/usuarios.h"
#include "transacciones/transacciones.h"
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define TIMEOUT_SEC 1
#define FIFO_INICIO "/tmp/mi_fifo_inicio"
#define FIFO_CERRAR "/tmp/mi_fifo_cerrar"
volatile bool detener_hilos_logs = false;
int *listaUsuarios;
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
    printf("ANOMALÍA %d\n", codigo_anomalia);
}

//------------------------------ FUNCIONES DE LOS HILOS PARA DETECTAR ANOMALÍAS ------------------------------

// Detección de fondos insuficientes
void *hilo_fondos_insuficientes(void *arg) {       
  printf("Hilo fondos insuficientes\n");
  return NULL;
}

// Detección de transacciones demasiado grandes
void *hilo_transacciones_grandes(void *arg) {
  printf("Hilo transacciones grandes %d\n",nusers);  
  FILE *archivo;
  char nombre_archivo[50];
  char linea[256];
  for(int i=0; i<nusers;i++){
    if(listaUsuarios[i]==0)
      continue;
    sprintf(nombre_archivo, "./ficheros/%d/transacciones.log", 1001 + i);
    archivo = fopen(nombre_archivo, "r");
    if(archivo==NULL){
      printf("No se ha podido abrir el fichero %s\n",nombre_archivo);
      continue;
    }
    else {
      while (fgets(linea, 256, archivo)){
        
      }
      printf("Se a abierto el fichero %s\n",nombre_archivo);
    }
    fclose(archivo);
  }

  return NULL;
}

// Detección de muchas secuencias inusuales en poco tiempo (3 transacciones en menos de 1 minuto)

void *hilo_secuencia_inusual(void *arg) {
  printf("Hilo secuencia inusual\n");  
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
              if (!posiciones) {
                  perror("Error en realloc");
                  break;
              }
              // Inicializa nuevos elementos a 0
              for (int i = nusers; i < nuevo_tam; i++) {
                  nuevo[i] = 0;
              }
              listaUsuarios = nuevo;
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

void hilos(pthread_t *hilo_fondos, pthread_t *hilo_transacciones,  pthread_t *hilo_secuencia){
  
  // Crear hilos para anomalías
  pthread_create(hilo_fondos, NULL, hilo_fondos_insuficientes, NULL);
  pthread_create(hilo_transacciones, NULL, hilo_transacciones_grandes, NULL);
  pthread_create(hilo_secuencia, NULL, hilo_secuencia_inusual, NULL);

  // CODIGO PARA LEER TRANSACCIONES Y CUENTAS
  pthread_join(*hilo_fondos, NULL);
  pthread_join(*hilo_transacciones, NULL);
  pthread_join(*hilo_secuencia, NULL);
}
//------------------------------ MONITOR PRINCIPAL ------------------------------

// Función monitor principal

int main(int argc, char *argv[]) {

  InitGlobal();
  nusers=1;
  pthread_mutex_init(&mutex, NULL);
  listaUsuarios=calloc(1,sizeof(int));

  pthread_t hilo_fondos, hilo_transacciones, hilo_secuencia, hilo_login,hilo_cerrar;
  
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
  pthread_create(&hilo_cerrar, NULL, hilo_comprobar_login, &fd_lectura_cerrar);

  while (!detener_hilos_logs) {
    hilos(&hilo_fondos, &hilo_transacciones, &hilo_secuencia);
  }
  
  pthread_join(hilo_login, NULL);
  pthread_join(hilo_cerrar, NULL);
  
  return 0;
}
