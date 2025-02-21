#!/bin/bash
read -p "¿Está seguro de que desea borrar el directorio MiDirectorio? [y/n] " confirm
Variable=0
if [ "$confirm" = "y" ]; then
  for file in ./MiDirectorio/*; do
    read -p "Estas seguro que quiere eliminar el fichero $file? [y/n]" confirm 
    if [ "$confirm" = "y" ]; then
      Variable++
      rm $file
      echo "Se elimino el archivo: $file" >> archivos-eliminados.txt
    fi 
  done
  if [[ Variable!=0 ]]; then
    rm -rf MiDirectorio
    echo "MiDirectorio y su contenido han sido eliminados."
  else
    echo "MiDirectorio no se a borrado por que no quieres eliminar ningun fichero"
  fi

else
  echo "Operación cancelada."
fi
