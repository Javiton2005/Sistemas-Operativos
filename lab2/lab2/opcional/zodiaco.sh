#! /bin/bash

while [[ true ]]; do
  
  while [[ true ]]; do
    echo "Introduce el dia de nacimiento (numero)"
    read -r dia
    if [[ $dia -lt 32 && $dia -gt 0 ]]; then

      break
    fi
    clear
    echo "Introduce un dia del mes valido"
  done
  while [[ true ]]; do 
    echo "Introduce el mes de nacimiento (numero)"
    read -r mes
    if [[ $mes -lt 13 && $mes -gt 0 ]]; then
      break  
    fi
    echo "Introduce un mes del año valido"
  done

  if [[ $mes -eq 2 && $dia -lt 30 ]]; then
    echo "Tu fecha de nacimiento es: $dia/$mes"
    break   
  fi
  clear
  echo "El mes de febrero no tiene mas de 29 dias"
done
