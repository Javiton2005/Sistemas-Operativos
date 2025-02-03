@ECHO OFF
SET "sourceDir=C:\Users\jocra\Desktop\windows\MiDirectorio"
SET "outputFile=combined.txt"

SET /p "excludeWord=Ingrese la palabra que desea excluir: "

IF "%excludeWord%"=="" (
    ECHO No hay ninguna palabra para excluir.
    PAUSE
    GOTO END
)

IF EXIST "%outputFile%" DEL "%outputFile%"

FOR %%f IN ("%sourceDir%\*.txt") DO (
  ECHO Combinando: %%~nxf

  SET "tempFile=%%~dpnf_temp.txt"

  FINDSTR /v /i /c:"%excludeWord%" "%%f" > "%tempFile%"

  MOVE /Y "%tempFile%" "%%f" > NUL

  TYPE "%%f" >> "%outputFile%"
  ECHO. >> "%outputFile%" 
  ECHO. >> "%outputFile%" 
)

ECHO Todos los archivos .txt han sido combinados en %outputFile%.
PAUSE
