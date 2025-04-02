#include <stdio.h>
#include <stdlib.h>
int global_var = 10; // Segmento .data
int uninit_var; // Segmento .bss

void print_message() { // Segmento .text
  printf("Hola desde la función\n");
}

int main() {
  int local_var = 5; // Pila (stack)
  int *heap_var = malloc(sizeof(int)); // Montículo (heap)
  *heap_var = 20;
  printf("Global: %d, Local: %d, Heap: %d\n", global_var, local_var, *heap_var);
  print_message();
  free(heap_var);
  return 0;
}
