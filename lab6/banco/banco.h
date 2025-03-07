#ifdef BANCO_H
  #define BANCO_H 

typedef struct _USER{
  char *nombre;
  int *numeroCuenta;
  double *saldo;
  int *tarjetas;
}USER;

// Función para crear un usuario (prototipo)
USER crearUsuario(const char *nombre, int numeroCuenta, double saldo, int tarjetas);

#endif // BANCO_H

