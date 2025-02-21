#! /bin/bash
if [[ "$1" =~ ^[0-9]+$ ]]; then 
  for ((i = 0; i < 13; i++)); do
    echo "$1 * $i = $(($1*$i))"
  done
else
  echo "Esto no es un numero"
fi
 


