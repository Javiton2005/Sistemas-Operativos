#! /bin/bash

if [[ -z $1 || -z $2 ]]; then
  echo "Carpeta tipo de compresion (zip/tar)"
  echo "Faltan parametros"
  exit 
fi

if [[ -d $1 ]]; then
  if [[ $2 == "zip" ]]; then
    zip -r $1.zip $1
  elif [[ $2 == "tar" ]]; then
    tar -cf $1.tar $1
  else
    echo "Especibica el formato de comrpesion"
  fi
else
  echo "El directorio/fichero no existe" 
fi
