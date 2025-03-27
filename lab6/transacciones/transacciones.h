#ifndef TRANSACCIONES_H
#define TRANSACCIONES_H

#include "../comun/comun.h"

USER *crearTransaccion(char *linea, int nLinea);
USER **CrearListaTransacciones(char *fichero);

#endif // TRANSACCIONES_H

