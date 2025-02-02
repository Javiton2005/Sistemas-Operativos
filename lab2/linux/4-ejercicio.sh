#!/bin/bash
targetDir="./Ejercicio-4"
outputFile="archivos_seleccionados.txt"

patron="$1"
> "$outputFile"

for file in "$targetDir"/*.txt; do
  if [[ -f "$file" && ( -z "$patron" || ! "$file" == *"$patron"*)]]; then
        echo "$file" >> "$outputFile"
    fi
done

echo "Archivos .txt listados en $outputFile"
cat $outputFile
