#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para sleep() y getpid()
#include <sys/time.h> // Para medir tiempo
#define MB (1024 * 1024) // 1 MB en bytes
#define SIZE_MB 2048 // Tamaño total a reservar (2 GB)
// Función para leer y mostrar información de memoria desde
//proc/meminfo 
void print_memory_info() {
  FILE *meminfo = fopen("/proc/meminfo", "r");
  if (!meminfo) {
    perror("No se pudo abrir /proc/meminfo");
    return;
  }
  char line[256];
  while (fgets(line, sizeof(line), meminfo)) {
    if (strstr(line, "MemTotal") || strstr(line, "MemFree") ||
      strstr(line, "SwapTotal") || strstr(line, "SwapFree")) {
      printf("%s", line);
    }
  }
  fclose(meminfo);
}
int main() {
  pid_t pid = getpid(); // Obtener el ID del proceso
  printf("PID del proceso: %d\n", pid);
  printf("Información inicial de memoria:\n");
  print_memory_info();
  // 1. Reservar memoria virtual (sin tocarla aún)
  size_t size = 4294967296;//SIZE_MB * MB; // 2 GB
  char *buffer = (char *)malloc(size);
  if (!buffer) {
    perror("Error al asignar memoria");
    return 1;
  }
  printf("\nReservados %d MB de memoria virtual con malloc.\n",SIZE_MB);
  printf("La RAM aún no se usa porque no hemos accedido a la memoria.\n");
  sleep(5); // Pausa para observar con 'top' o 'htop'
  // 2. Acceder a la memoria para forzar uso de RAM y posible swapping
  printf("\nAccediendo a toda la memoria (esto puede forzar swapping)...\n");
  struct timeval start, end;
  gettimeofday(&start, NULL);
  // Escribir en cada página (tamaño típico de página: 4 KB)
  for (size_t i = 0; i < size; i += 4096) {
    buffer[i] = 'A'; // Toca cada página
  }
  gettimeofday(&end, NULL);
  double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
  printf("Memoria tocada en %.2f segundos.\n", time_taken);
  printf("Información después de tocar la memoria:\n");
  print_memory_info();
  // 3. Mantener el proceso vivo para inspeccionar con herramientas externas
  printf("\nProceso pausado. Usa 'top', 'htop' o 'free' para ver RAM y swap.\n");
  printf("Presiona Ctrl+C para terminar.\n");
  while (1) {
    sleep(1); // Mantener el proceso activo
  }
  free(buffer); // Liberar memoria (no llegaremos aquí por el bucle)
  return 0;
}
