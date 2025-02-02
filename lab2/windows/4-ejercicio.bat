@ECHO OFF
SET "targetDir=C:\ruta\del\directorio"
SET "outputFile=archivos_seleccionados.txt"
DEL %outputFile% 2>NUL
FOR %%i IN (%targetDir%\*) DO (
  IF "%%~xi"==".txt" (
    ECHO %%i >> %outputFile%
  )
)
ECHO Archivos .txt listados en %outputFile%
PAUSE
