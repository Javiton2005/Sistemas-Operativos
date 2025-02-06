
IF "%~1"=="" (
    ECHO Por favor, especifique una extension de archivo como parametro (ejemplo: .txt).
    PAUSE
    EXIT /B
)

SET "C:\Users\jdpv6\OneDrive\Documentos\SSOO\Lab2"
SET "outputFile=archivos_seleccionados.txt"

DEL %outputFile% 2>NUL

FOR %%i IN (%targetDir%\*) DO (
    IF "%%~xi"=="%~1" (
		ECHO %%i >> %outputFile%
)
)

ECHO Archivos con la extensión %~1 listados en %outputFile%.
PAUSE
