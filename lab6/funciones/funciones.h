#ifndef FUNCIONES
  #define FUNCIONES

#include "../comun/comun.h"
#include "../usuarios/usuarios.h"
extern char *funcionesMenu[];

void MenuOpciones();

int SacarDinero();
int MeterDinero();
int ConsultarSaldo();
int InfoCuenta();
int Transaccion();
int PagarTasas();
int CancelarTarjetas();

#endif // FUNCIONES

