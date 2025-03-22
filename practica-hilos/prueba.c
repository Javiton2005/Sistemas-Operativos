#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_USERS 100
#define LINE_LENGTH 256

// Estructura del usuario
typedef struct {
    char username[50];
    char password[50];
    double balance;
} Usuario;

// Manejo de procesos zombis
void limpiar_zombies(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

// Carga usuarios desde el CSV
int cargar_usuarios(Usuario usuarios[]) {
    FILE *file = fopen("usuarios.csv", "r");
    if (!file) {
        perror("Error abriendo el archivo CSV");
        exit(1);
    }

    int i = 0;
    char line[LINE_LENGTH];
    while (fgets(line, sizeof(line), file) && i < MAX_USERS) {
        sscanf(line, "%49[^,],%49[^,],%lf", usuarios[i].username, usuarios[i].password, &usuarios[i].balance);
        i++;
    }
    fclose(file);
    return i;
}

// Autentica usuario
int autenticar_usuario(Usuario usuarios[], int total, char *username, char *password) {
    for (int i = 0; i < total; i++) {
        if (strcmp(usuarios[i].username, username) == 0 && strcmp(usuarios[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

// Proceso hijo: Manejar sesión
void manejar_usuario(Usuario usuario) {
    printf("\n[PID: %d] Bienvenido, %s!\n", getpid(), usuario.username);
    printf("[PID: %d] Tu saldo actual es: $%.2f\n", getpid(), usuario.balance);
    sleep(10);  // Simula operaciones bancarias
    printf("[PID: %d] Sesión finalizada para %s\n", getpid(), usuario.username);
    exit(0);
}

// MAIN
int main() {
    Usuario usuarios[MAX_USERS];
    int total_usuarios = cargar_usuarios(usuarios);
    
    // Manejar señal para limpiar procesos zombis
    signal(SIGCHLD, limpiar_zombies);

    while (1) {  // Aceptar múltiples inicios de sesión
        char username[50], password[50];

        printf("\nIngrese usuario: ");
        scanf("%s", username);
        printf("Ingrese contraseña: ");
        scanf("%s", password);

        int id_usuario = autenticar_usuario(usuarios, total_usuarios, username, password);
        if (id_usuario != -1) {
            pid_t pid = fork();

            if (pid < 0) {
                perror("Error al crear proceso hijo");
            } else if (pid == 0) {
                manejar_usuario(usuarios[id_usuario]);  // Código del proceso hijo
            } else {
                printf("[MAIN] Usuario autenticado, proceso hijo creado con PID: %d\n", pid);
            }
        } else {
            printf("Usuario o contraseña incorrectos\n");
        }
    }

    return 0;
}

