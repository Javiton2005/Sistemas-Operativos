@ECHO OFF

SET logfile=log.txt

DIR MiDirectorio /B /S >> %logfile%

ECHO Directorios a eliminar:
TYPE %logfile%

SET /P confirm="¿Está seguro de que desea borrar el directorio MiDirectorio? [y/n] "
IF /I "%confirm%" NEQ "y" EXIT
RD /S /Q MiDirectorio
ECHO MiDirectorio y su contenido han sido eliminados.

PAUSE

