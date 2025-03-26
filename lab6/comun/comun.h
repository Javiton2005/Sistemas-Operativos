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


typedef struct _User{
  char *nombre;
  char *contrasena;
  char *ncuenta;
  int saldo;
  int ntrasacciones;
  int id;

} USER;

extern struct _Config {
  int limite_retiro;
  int limite_transferencia;
  int umbral_retiros;
  int umbral_transferencias;
  int num_hilos;
  char archivo_cuentas[50];
  char archivo_log[50];
} Config;

extern struct _Estadisticas {
  int usuarios;
} Estadisticas;

void InitGlobal();
void EscribirEnLog(char *frase);
USER *leerCsv(int *idUser);

void *EditarCsv(void *usuario);
#endif // Comun_H
