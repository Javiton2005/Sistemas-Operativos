#ifndef USUARIOS_H
  #define USUARIOS_H

#include "../comun/comun.h"

void crearUsuario(char *linea, int id, USER *user);

void CrearListaUsuarios(TABLA_USUARIOS *tabla, char *fichero);

#endif // USUARIOS_H
