#!/bin/bash
@Echo off
if [ $# -eq 0 ]; then
  echo "Por favor, especifique el nombre del archivo como parámetro."
  exit 1
fi
mkdir -p MiDirectorio
echo "Creando archivo: $1 en MiDirectorio"
if [[ $# -eq 1 ]]; then
  echo "Ingrese el contenido del fichero"
  read -r contenido
  echo "$contenido" > MiDirectorio/$1
else
 echo "$2" > MiDirectorio/$1 
fi

