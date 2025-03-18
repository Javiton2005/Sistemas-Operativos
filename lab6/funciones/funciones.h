#ifndef FUNCIONES
  #define FUNCIONES

#include "../comun/comun.h"

extern char *funcionesMenu[];

void *MenuOpciones(void *usuario);

void *SacarDinero(void *usuario);
void *MeterDinero(void *usuario);
void *ConsultarSaldo(void *usuario);
void *InfoCuenta(void *usuario);
void *Transaccion(void *usuario);
void *PagarTasas(void *usuario);
void *CancelarTarjetas(void *usuario);
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

