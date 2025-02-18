@ECHO OFF

IF "%~1"=="" (
    ECHO Por favor, especifique el nombre del archivo como parametro.
    PAUSE
    EXIT /B
)

SET "file=%~1"

IF NOT EXIST "%file%" (
    ECHO El archivo no existe. Creando el archivo: %file%
    ECHO. > "%file%"  :: Crea un archivo vacío
)

START NOTEPAD "%file%"

ECHO El Bloc de notas se ha abierto con el archivo: %file%
PAUSE
