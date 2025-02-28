#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
// Manejador de la señal
void manejador(int senal) {
  printf("Se recibió la señal %d dentro del mismo proceso.\n", senal);
}
int main() {
  signal(SIGUSR1, manejador); // Configurar manejador para SIGUSR1
  printf("Enviando SIGUSR1 a sí mismo...\n");
  raise(SIGUSR1); // Enviar la señal SIGUSR1 al mismo proceso
  printf("Fin del programa.\n");
  return 0;
}
