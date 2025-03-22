#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void iniciar_en_nueva_terminal(char *usuario) {
    pid_t pid = fork();
    if (pid == 0) {  // Proceso hijo
        int fd = open("/dev/null", O_WRONLY);
        dup2(fd, STDERR_FILENO);  // Redirige errores a /dev/null
        close(fd);

        execlp("kitty", "kitty", "sh", "-c", "./prueba", usuario, (char *)NULL);
        perror("Error al ejecutar kitty");
        exit(1);
    }
}

int main() {
    char usuario[50];

    while (1) {
        printf("\nIngrese usuario: ");
        scanf("%s", usuario);

        iniciar_en_nueva_terminal(usuario);
        printf("[MAIN] Se ha abierto una nueva terminal para %s\n", usuario);
    }

    return 0;
}
