#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
// Manejador de la señal SIGALRM
void manejador(int signo) {
  printf("¡Alarma activada! Se recibió la señal %d\n", signo);
}
int main() {
  signal(SIGALRM, manejador); // Asociar SIGALRM con el manejador
  printf("Se programó una alarma en 3 segundos...\n");
  alarm(3); // Programar la alarma en 3 segundos
  pause(); // Espera una señal (para que el programa no termine antes)
  printf("Fin del programa.\n");
  return 0;
}
