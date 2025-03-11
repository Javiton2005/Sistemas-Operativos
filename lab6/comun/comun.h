#ifndef Comun_H
#define Comun_H

#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <threads.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>

typedef struct _User{
  char *nombre;
  char *contrasena;
  char *ncuenta;
  int saldo;
  int ntrasacciones;
} USER;


extern struct _Estadisticas {
  int usuarios;
} Estadisticas;

void InitGlobal();

#endif // Comun_H
