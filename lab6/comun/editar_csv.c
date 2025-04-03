#include "comun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *EditarCsv(void *usuario) {
    if (usuario == NULL) {
        perror("Error al pasar el usuario");
        exit(EXIT_FAILURE);
    }

    USER *user = (USER *)usuario;
    
    FILE *csv = fopen(Config.archivo_cuentas, "r"); // Modo lectura
    if (!csv) {
        perror("Error al abrir el archivo original");
        exit(EXIT_FAILURE);
    }

    FILE *temp = fopen("temp.csv", "w"); // Archivo temporal
    if (!temp) {
        perror("Error al crear el archivo temporal");
        fclose(csv);
        exit(EXIT_FAILURE);
    }

    char buffer[255];
    int contador = 0;

    while (fgets(buffer, sizeof(buffer), csv)) {
        if (contador == user->id) {
            // Reemplazar la línea del usuario
            fprintf(temp, "%s;%s;%s;%.2lf\n", user->nombre, user->contrasena, user->ncuenta, user->saldo);
        } else {
            // Copiar la línea original al archivo temporal
            fprintf(temp, "%s", buffer);
        }
        contador++;
    }

    fclose(csv);
    fclose(temp);

    // Reemplazar el archivo original con el nuevo archivo modificado
    remove(Config.archivo_cuentas);
    rename("temp.csv", Config.archivo_cuentas);

    return NULL;
}
