@echo off

SET "targetDir=%cd%"
SET "outputFile=%cd%\archivos_seleccionados.txt"

REM Eliminar el archivo de salida si ya existe
IF EXIST "%outputFile%" DEL "%outputFile%"

FOR %%i IN (%targetDir%\*) DO (
    IF "%%~xi"=="%~1" (
		ECHO %%ii >> %outputFile%
)
)

ECHO Archivos con la extension %~1 listados en %outputFile%
PAUSE
