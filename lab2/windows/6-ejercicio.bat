@ECHO OFF

CALL script1.bat
IF %ERRORLEVEL% NEQ 0 (
    ECHO [%DATE% %TIME%] Error al ejecutar script1.bat. Código de salida: %ERRORLEVEL% > error.log
)

CALL script2.bat
IF %ERRORLEVEL% NEQ 0 (
    ECHO [%DATE% %TIME%] Error al ejecutar script2.bat. Código de salida: %ERRORLEVEL% > error.log
)

PAUSE
