#ifndef Comun_H
#define Comun_H

#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <threads.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stddef.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FIFO_CERRAR "/tmp/mi_fifo_cerrar"
#define FIFO_INICIO "/tmp/mi_fifo_inicio"

#define ESTADO_APROBADA 0
#define ESTADO_FONDOS_INSUFICIENTES 1
#define ESTADO_TRANSACCION_GRANDE 2
#define ESTADO_LOGIN_FALLIDO 3
#define ESTADO_SECUENCIA_INUSUAL 4
#define ESTADO_USUARIO_NO_EXISTE 5
#define ESTADO_EXCEDE_LIMITE 6
#define ESTADO_CONSTRASENA_INCORRECTA 7
#define MAX_USUARIOS 100
#define MAX_NOMBRE 50
#define MAX_CUENTA 10

typedef struct _User{
  char nombre[MAX_NOMBRE];
  char contrasena[MAX_NOMBRE];
  char ncuenta[MAX_CUENTA];
  double saldo;
  int id;
  int bloqueado;
} USER;

typedef struct _TablaUsuarios{
  USER usuarios[MAX_USUARIOS];
  int num_usuarios;
} TABLA_USUARIOS;

typedef struct {
  int prioridad;
  USER operacion;
} Operacion;

typedef struct _Transaccion{
  double cantidad;
  char *ncuentas;
  char *ncuentao;
  struct tm fecha;
  char *descripcion;
} TRANSACCION;

extern struct _Config {
  int limite_retiro;
  int limite_transferencia;
  int umbral_retiros;
  int umbral_transferencias;
  int num_hilos;
  char archivo_cuentas[50];
  char archivo_log[50];
  char archivo_tranferencias[50];
  char archivo_log_transferencias[50];
  int limite_login;
  char clave[50];
  int fd_escritura_cerrar;
  int fd_escritura_inicio;
} Config;

extern struct _Estadisticas {
  int num_transacciones;
  int usuarios;
} Estadisticas;

void InitGlobal();
void EscribirEnLog(char *frase);
USER *leerCsv(int *idUser);

int *LeerCSVNcuenta(char *ncuenta);
void *EditarCsv(USER *usuario);
#endif // Comun_H
