@ECHO OFF
MD BatchWorkshop
CD BatchWorkshop

IF EXIST README.txt (
    FOR /F "usebackq" %%A IN (README.txt) DO SET fileContent=%%A
    IF DEFINED fileContent (
        ECHO Fecha y Hora de la última modificación: %DATE% %TIME% >> README.txt
    ) ELSE (
        ECHO Bienvenido al Taller de Batch > README.txt
        ECHO Este es un archivo README de ejemplo >> README.txt
    )
) ELSE (
    ECHO Bienvenido al Taller de Batch > README.txt
    ECHO Este es un archivo README de ejemplo >> README.txt
)

PAUSE

