@ECHO OFF
IF "%~1"=="" (
  ECHO Por favor, especifique el nombre del archivo como parámetro.
  PAUSE
  EXIT /B
)
MD MiDirectorio
ECHO Creando archivo: %1 en MiDirectorio > MiDirectorio\%1 ECHO Este es un archivo de prueba.
PAUSE
