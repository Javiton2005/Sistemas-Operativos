#ifndef USUARIOS_H
  #define USUARIOS_H

#include "../comun/comun.h"

USER *crearUsuario(char *linea, int nLinea);
USER **CrearListaUsuarios(char *fichero);

#endif // USUARIOS_H
