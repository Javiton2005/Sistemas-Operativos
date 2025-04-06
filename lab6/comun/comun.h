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

#define ESTADO_APROBADA 0
#define ESTADO_FONDOS_INSUFICIENTES 1
#define ESTADO_TRANSACCION_GRANDE 2
#define ESTADO_LOGIN_FALLIDO 3
#define ESTADO_SECUENCIA_INUSUAL 4
#define ESTADO_USUARIO_NO_EXISTE 5
#define ESTADO_EXCEDE_LIMITE 6
#define ESTADO_CONSTRASENA_INCORRECTA 7

typedef struct _User{
  char *nombre;
  char *contrasena;
  char *ncuenta;
  double saldo;
  int id;
} USER;

typedef struct _Transaccion{
  double cantidad;
  char *ncuentas;
  char *ncuentao;
  struct tm *fecha;
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
} Config;

extern struct _Estadisticas {
  int usuarios;
  int num_transacciones;
} Estadisticas;

void InitGlobal();
void EscribirEnLog(char *frase);
USER *leerCsv(int *idUser);

int *LeerCSVNcuenta(char *ncuenta);
void *EditarCsv(USER *usuario);
#endif // Comun_H
