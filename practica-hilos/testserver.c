#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void daemonizar() {
    pid_t pid = fork();

    if (pid < 0) exit(1);  // Error en fork
    if (pid > 0) exit(0);  // Termina el proceso padre

    // Crear una nueva sesión
    if (setsid() < 0) exit(1);

    // Redirigir la salida a /dev/null
    freopen("/dev/null", "r", stdin);
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);

    chdir("/");  // Cambia directorio para evitar bloqueos

    umask(0);  // Restablece permisos
}

int main() {
    printf("servidor on\n");
    daemonizar();  // Convierte el servidor en un demonio

    while (1) {
        sleep(10000);  // Simulación de que sigue corriendo
    }

    return 0;
}

