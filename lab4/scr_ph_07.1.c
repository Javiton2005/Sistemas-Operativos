#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int num1 = 0, num2 = 0; // Variables para almacenar los números
    char *cadena = NULL; // Variable para almacenar la cadena

    // Definir las opciones largas y cortas
    static struct option long_options[] = {
        {"cadena", required_argument, 0, 'c'},
        {"num1",   required_argument, 0, 'n'},
        {"num2",   required_argument, 0, 'm'},
        {"version", no_argument,       0, 'v'},
        {"date",    no_argument,       0, 'd'},
        {"name",    no_argument,       0, 'N'},
        {"last",    no_argument,       0, 'l'},
        {"full",    no_argument,       0, 'f'},
        {"birth",   no_argument,       0, 'b'},
        {0, 0, 0, 0}
    };

    int long_index = 0;
    int opt = 0;

    // Procesar las opciones pasadas
    while ((opt = getopt_long(argc, argv, "c:n:m:v:d:N:l:f:b", long_options, &long_index)) != -1) {
        switch (opt) {
            case 'c':
                cadena = optarg;
                break;
            case 'n':
                num1 = atoi(optarg);
                break;
            case 'm':
                num2 = atoi(optarg);
                break;
            case 'v':
                printf("Versión 0.1.0 - Fase Alpha\n");
                return 0;
            case 'd':
                printf("Fecha: Día de pierna no, te lo aseguro\n");
                return 0;
            case 'N':
                printf("Nombre: Juan Diego\n");
                return 0;
            case 'l':
                printf("Apellido: Panchón\n");
                return 0;
            case 'f':
                printf("Nombre completo: Juan Diego Panchón\n");
                return 0;
            case 'b':
                printf("Fecha de nacimiento: 32-13-2105\n");
                return 0;
            default:
                printf("Uso: %s --cadena <cadena> --num1 <numero1> --num2 <numero2> [opciones]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Verificar que todos los parámetros requeridos fueron proporcionados
    if (cadena == NULL || num1 == 0 || num2 == 0) {
        printf("Todos los parámetros son requeridos\n");
        printf("Uso: %s --cadena <cadena> --num1 <numero1> --num2 <numero2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Imprimir la cadena y el resultado de la multiplicación
    printf("Cadena recibida: %s\n", cadena);
    printf("Resultado de %d * %d = %d\n", num1, num2, num1 * num2);

    return 0;
}