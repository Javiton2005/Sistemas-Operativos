#! /bin/bash

if [[ $1 -lt 15 && $1 -gt 0 ]]; then
  echo "Valor 1"

elif [[ $1 -lt 56 && $1 -gt 14 ]]; then
  echo "Valor 2"

elif [[ $1 -lt 100 && $1 -gt 55 ]]; then
  echo "valor 3"

elif [[ $1 -lt 200 && $1 -gt 100 ]]; then
  echo "valor 4"
else
  echo "Valor 5"
fi


