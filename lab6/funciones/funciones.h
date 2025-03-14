#ifndef FUNCIONES
  #define FUNCIONES

#include "../comun/comun.h"

extern char *funcionesMenu[];

void MenuOpciones(USER *registrado);

int SacarDinero();
int MeterDinero();
int ConsultarSaldo(USER *registrado);
int InfoCuenta(USER *registrado);
int Transaccion();
int PagarTasas();
int CancelarTarjetas();

#endif // FUNCIONES

