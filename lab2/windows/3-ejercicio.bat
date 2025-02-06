@ECHO OFF
IF "%~1"=="" (
  ECHO Por favor, especifique al menos un nombre de archivo como parámetro.
  PAUSE
  EXIT /B
)

MD MiDirectorio

:loop
IF "%~1"=="" GOTO end

ECHO Ingrese el contenido para el archivo "%~1":
SET /P contenido=

ECHO %contenido% > MiDirectorio\%~1

ECHO Archivo "%~1" creado en MiDirectorio con el contenido proporcionado.

SHIFT
GOTO loop

:end
PAUSE