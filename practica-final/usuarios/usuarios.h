#ifndef USUARIOS_H
  #define USUARIOS_H

#include "../comun/comun.h"
#include "../funciones/funciones.h"
void crearUsuario(char *linea, int id, USER *user);

void CrearListaUsuarios(TABLA_USUARIOS *tabla, char *fichero);

void *EscribirEnLogHilo(void *arg);
#endif // USUARIOS_H
