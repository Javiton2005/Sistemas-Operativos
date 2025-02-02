#!/bin/bash

if [[ -d "./BatchWorkshop/" ]]; then
  mkdir -p BatchWorkshop  
fi

if [[ -f "./BatchWorkshop/README.txt" ]]; then
  date >> BatchWorkshop/README.txt  
else
  echo "Bienvenido al Taller de Bash" > BatchWorkshop/README.txt
  echo "Este es un archivo README de ejemplo" >> BatchWorkshop/README.txt
fi

cat ./BatchWorkshop/README.txt
