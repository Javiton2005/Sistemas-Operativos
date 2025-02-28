#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void manejar_senal(int senal) {
  printf("Se recibió la señal %d\n", senal);
}
int main() {
  signal(SIGINT, manejar_senal); // Captura Ctrl + C
  while (1) {
    printf("Ejecutando...\n");
    sleep(1);
  }
  return 0;
}
