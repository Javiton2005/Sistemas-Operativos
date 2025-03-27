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
#include <stdio.h>
#include <time.h>

#define MAX_TRANSACCION 1000

typedef struct _User{
  char *nombre;
  char *contrasena;
  unsigned int ncuenta;
  double saldo;
  int ntransacciones;
  TRANSACCION transaccion;
} USER;
typedef struct _Transaccion{
  double cantidad;
  unsigned int ncuentas;
  unsigned int ncuentao;
  struct tm *fecha;
  char *descripcion;
} TRANSACCION;

extern struct _Estadisticas {
  int usuarios;
} Estadisticas;

void InitGlobal();

#endif // Comun_H
