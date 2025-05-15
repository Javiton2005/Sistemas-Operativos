#ifndef USUARIOS_H
  #define USUARIOS_H

#include "../comun/comun.h"

USER crearUsuario(char *linea, int id);

void CrearListaUsuarios(TABLA_USUARIOS **tabla, char *fichero);

#endif // USUARIOS_H
