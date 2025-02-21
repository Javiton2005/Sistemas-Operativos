#!/bin/bash

#date  Esto muestra "sáb 01 feb 2025 20:32:02 CET"

dia=$(date | awk '{print $1}')
echo "La fecha y hora son"
date
echo "El dia de la semana es: $dia"
echo -n "Faltan "

case $dia in 
  lun)
    echo -n "5 dias "
    ;;

  mar)
    echo -n "4 dias "
    ;;

  mie)
    echo -n "3 dias "
    ;;

  jue)
    echo -n "2 dias "
    ;;

  vie)
    echo -n "1 dias "
    ;;
  
  sáb | dom)
    echo -n "0 dias "
    ;;

esac

echo  "para el finde semana"
