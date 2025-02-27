#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int num1, num2;
    switch (argc) {
        case 1:
            printf("Uso: %s <cadena> <numero1> <numero2>\n", argv[0]);
            printf("No has puesto ningun parametro, serán 0\n");
            argv[1] = NULL;
            num1 = 0;
            num2 = 0;
            break;
        case 2:
            printf("Uso: %s <cadena> <numero1> <numero2>\n", argv[0]);
            printf("Te faltan dos números, serán 0\n");
            num1 = 0;
            num2 = 0;
            break;
        case 3:
            printf("Uso: %s <cadena> <numero1> <numero2>\n", argv[0]);
            printf("Te faltan un número, será 0\n");
            num1 = atoi(argv[2]);
            num2 = 0;
            break;
        case 4:
            printf("Bravo, has puesto relleno en los argumentos. Esperemos que esté bien\n");
            num1 = atoi(argv[2]);
            num2 = atoi(argv[3]);
            break;
        default:
                printf("Uso: %s <cadena> <numero1> <numero2>\n", argv[0]);
                printf("Lo has logrado: has puesto de manera horrible los argumentos de esta función.\nSaliendo...\n");
                return 1;
    }

        // Imprimir la cadena recibida
        printf("Cadena recibida: %s\n", argv[1]);

        // Convertir los argumentos numéricos de char* a int (o float si necesitas decimales)
        

        // Realizar la multiplicación
        int resultado = num1 * num2;

        // Imprimir el resultado
        printf("Resultado de %d * %d = %d\n", num1, num2, resultado);

    return 0;
}