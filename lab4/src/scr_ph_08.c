#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main(int argc, char *argv[]) {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *key, *value;
    char username[MAX_LINE_LENGTH] = "";
    char password[MAX_LINE_LENGTH] = "";
    char *path;
    int num, num_pthread;
    switch (argc) {
        case 1:
            printf("Uso: %s <path> <numero> <pthread>\n", argv[0]);
            printf("No has puesto ningun parametro, serán 0\n");
            path = (char*)NULL;
            num = 0;
            num_pthread = 0;
            break;
        case 2:
            printf("Uso: %s <path> <numero> <pthread>\n", argv[0]);
            printf("Te faltan un número y pthread, serán 0\n");
            path = argv[1];
            num = 0;
            num_pthread = 0;
            break;
        case 3:
            printf("Uso: %s <path> <numero> <pthread>\n", argv[0]);
            printf("Te faltan pthread, será 0\n");
            num = atoi(argv[2]);
            num_pthread = 0;
            break;
        case 4:
            printf("Bravo, has puesto relleno en los argumentos. Esperemos que esté bien\n");
            path = argv[1];
            num = atoi(argv[2]);
            num_pthread = atoi(argv[3]);
            break;
        default:
                printf("Uso: %s <path> <numero> <pthread>\n", argv[0]);
                printf("Lo has logrado: has puesto de manera horrible los argumentos de esta función.\nSaliendo...\n");
                return 1;
    }

    printf("%s\n", path);
    // Abre el fichero de properties
    file = fopen(path, "r");
    if (!file) {
        perror("No se pudo abrir el archivo");
        return EXIT_FAILURE;
    }

    // Lee el fichero línea por línea
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        // Elimina el salto de línea al final, si existe
        line[strcspn(line, "\n")] = 0;

        // Divide la línea en clave y valor
        key = strtok(line, "=");
        value = strtok(NULL, "=");

        // Comprueba si la clave y el valor son válidos y guarda los datos
        if (key && value) {
            if (strcmp(key, "username") == 0) {
                strncpy(username, value, MAX_LINE_LENGTH);
            } else if (strcmp(key, "password") == 0) {
                strncpy(password, value, MAX_LINE_LENGTH);
            }
        }
    }

    // Cierra el fichero
    fclose(file);

    // Imprime las variables para verificar
    printf("Username: %s\n", username);
    printf("Password: %s\n", password);

    return EXIT_SUCCESS;
}