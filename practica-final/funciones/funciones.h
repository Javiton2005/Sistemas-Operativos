#ifndef FUNCIONES
  #define FUNCIONES

#include "../comun/comun.h"

extern char *funcionesMenu[];
extern TABLA_USUARIOS *tabla;

typedef struct _idValor{
  int *id;
  void *valor;
}IdValor;


typedef struct {
    IdValor *parametros;
    TABLA_USUARIOS *tabla;
} HiloArgs;

void MenuOpciones(IdValor *parametos);

void SacarDinero(int *idUser);
void MeterDinero(int *idUser);
void ConsultarSaldo(int *idUser);
void InfoCuenta(int *idUser);
void Transaccion(int *idUser);
void CancelarTarjeta(int *idUser);

void EscribirLogTrans(TRANSACCION *trans);
void RegistrarTransaccion(TRANSACCION *transaccion, int idUser);

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
