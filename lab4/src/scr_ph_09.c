#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_LINEA 256

// ./base/
// └── sub1/
//     └── sub2/


int main() {
    FILE *file = fopen("properties.txt", "r");
    if(!file){
	perror("Error al abrir archivo properties");
	return 1;
    } else {
        printf("Archivo properties abierto correctamente");
    }

    char line[MAX_LINEA]; //crea array para guardar lineas del archivo properties

    while(fgets(line, sizeof(line), file)) { //guarda en line contenido de array

        line[strcspn(line, "\n")] = 0; //remplaza \n con NULL

	if (mkdir(line, 0777) == -1) {
	    perror("Error al crear el directorio base");
    	} else {
	    printf("Directorio Creado: %s\n", line);
	}
    }

    fclose(file);

    printf("Estructura de directorios creada con éxito.\n");

    return 0;
}
