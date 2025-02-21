#! /bin/bash

if [[ $1 == "" ]]; then
  echo "Introduce el nombre del fichero"
  read -r Nombre
else
  Nombre=$1
fi

if [[ $2 == "" ]]; then
  echo "Introcude el contenido del fichero"
  read -r Contenido
else
  Contenido=$2
fi

if [[ $3 == "" ]]; then
  echo "Introduce el tamaño del fichero (MB)"
  read -r Tamano
else
  Tamano=$3
fi

truncate -s ${Tamano}M $Nombre

echo "$Contenido" >> ./$Nombre

