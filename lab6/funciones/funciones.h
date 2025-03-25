#ifndef FUNCIONES
  #define FUNCIONES

#include "../comun/comun.h"

extern char *funcionesMenu[];

void MenuOpciones(USER *usuario);

void SacarDinero(USER *usuario);
void MeterDinero(USER *usuario);
void ConsultarSaldo(USER *usuario); // Hecho
void InfoCuenta(USER *usuario);     // Hecho
void Transaccion(USER *usuario);     
void PagarTasas(USER *usuario);
void CancelarTarjetas(USER *usuario);
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
