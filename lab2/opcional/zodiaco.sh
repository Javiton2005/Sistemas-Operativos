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
    break
  else
    break
  fi
  clear
  echo "El mes de febrero no tiene mas de 29 dias"
done

if [[ ( $mes -eq 1 && $dia -lt 21 ) || ( $mes -eq 12 && $dia -gt 23 ) ]]; then
  echo "Capricornio"
elif [[ ($mes -eq 1 && $dia -gt 20 ) || ( $mes -eq 2 && $dia -lt 20 ) ]]; then
  echo "Acuario"
elif [[ ($mes -eq 2 && $dia -gt 19 ) || ( $mes -eq 3 && $dia -lt 21 ) ]]; then
  echo "Piscis"
elif [[ ($mes -eq 3 && $dia -gt 20 ) || ( $mes -eq 4 && $dia -lt 21 ) ]]; then
  echo "Aries"
elif [[ ($mes -eq 4 && $dia -gt 20 ) || ( $mes -eq 5 && $dia -lt 22 ) ]]; then
  echo "Tauro"
elif [[ ($mes -eq 5 && $dia -gt 21 ) || ( $mes -eq 6 && $dia -lt 22 ) ]]; then
  echo "Geminis"
elif [[ ($mes -eq 6 && $dia -gt 21 ) || ( $mes -eq 7 && $dia -lt 24 ) ]]; then
  echo "Cancer"
elif [[ ($mes -eq 7 && $dia -gt 23 ) || ( $mes -eq 8 && $dia -lt 24 ) ]]; then
  echo "Leo"
elif [[ ($mes -eq 8 && $dia -gt 23 ) || ( $mes -eq 9 && $dia -lt 24 ) ]]; then
  echo "Virgo"
elif [[ ($mes -eq 9 && $dia -gt 23 ) || ( $mes -eq 10 && $dia -lt 24 ) ]]; then
  echo "Libra"
elif [[ ($mes -eq 10 && $dia -gt 23 ) || ( $mes -eq 11 && $dia -lt 23 ) ]]; then
  echo "Escorpio"
elif [[ ($mes -eq 11 && $dia -gt 22 ) || ( $mes -eq 12 && $dia -lt 23 ) ]]; then
  echo "Sagitario"
fi
