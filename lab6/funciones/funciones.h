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
/*
   0 "Sacar Dinero",
   1 "Meter Dinero",
   2 "Consultar Saldo",
   3 "Informacion de la Cuenta",
   4 "Transaccion",
   5 "Pagar Tasas",
   6 "Cancelar Tarjetas"
*/
#endif // FUNCIONES

