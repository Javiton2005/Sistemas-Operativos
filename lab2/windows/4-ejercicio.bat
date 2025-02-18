@echo off

SET "targetDir=C:\Users\jdpv6\OneDrive\Documentos\SSOO\Lab2"
SET "outputFile=archivos_seleccionados.txt"

FOR %%i IN (%targetDir%\*) DO (
    IF "%%~xi"=="%~1" (
		ECHO %%ii >> %outputFile%
)
)

ECHO Archivos con la extension %~1 listados en %outputFile%
PAUSE
