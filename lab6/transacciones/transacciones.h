#ifndef TRANSACCIONES_H
  #define TRANSACCIONES_H

#include "../comun/comun.h"

TRANSACCION *crearTransaccion(char *linea, int nLinea);
TRANSACCION **CrearListaTransacciones(char *fichero);

#endif // TRANSACCIONES_H

