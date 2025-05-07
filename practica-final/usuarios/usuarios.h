#ifndef USUARIOS_H
  #define USUARIOS_H

#include "../comun/comun.h"

USER crearUsuario(char *linea, int id);

TABLA_USUARIOS *CrearListaUsuarios(char *fichero);

#endif // USUARIOS_H
