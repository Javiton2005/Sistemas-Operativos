#!/bin/bash
read -p "¿Está seguro de que desea borrar el directorio MiDirectorio? [y/n] " confirm
if [ "$confirm" = "y" ]; then
  for file in ./MiDirectorio/*; do
    read -p "Estas seguro que quiere eliminar el fichero $file? [y/n]" confirm 
    if [ "$confirm" = "y" ]; then
      echo "Se elimino el archivo: $file" >> archivos-eliminados.txt
    fi 
  done
  #rm -rf MiDirectorio
  #echo "MiDirectorio y su contenido han sido eliminados."
else
  echo "Operación cancelada."
fi
