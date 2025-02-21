#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 

int main() { 

  printf("Ejecutando 'ls' para listar los contenidos del directorio actual:\n"); 
  // Fork para crear un proceso hijo 
  pid_t pid = fork(); 
  if (pid == -1) { 
    // Si fork() devuelve -1, hubo un error al crear el proceso hijo 
    perror("Fork falló");
    exit(1); 
  } else if (pid == 0) { 
    // Estamos en el proceso hijo 
    // execl requiere la ruta completa del programa a ejecutar y luego los argumentos que se le pasan 
    // El primer argumento después de la ruta del programa es típicamente el nombre del programa 
  // El último argumento debe ser NULL para indicar el final de la lista de argumentos 

    execl("/bin/ls", "ls", "-l", (char *)NULL); 
    // Si execl retorna, hubo un error 
    perror("execl falló");
    exit(1); 
  } else { 
    // Estamos en el proceso padre 
    // Esperamos a que el proceso hijo termine wait(NULL); 
  }
  return 0; 
}
