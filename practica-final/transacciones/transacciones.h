#ifndef TRANSACCIONES_H
  #define TRANSACCIONES_H

#include "../comun/comun.h"

TRANSACCION *crearTransaccion(char *linea);
TRANSACCION **CrearListaTransacciones(char *fichero);

#endif // TRANSACCIONES_H

