#include <stdio.h>
#define FRAMES 3 // Número de marcos de página
#define PAGES 10 // Longitud de la secuencia de referencias
// Estructura para un marco de página
typedef struct {
  int page; // Número de página (-1 si está vacío)
  int order; // Orden de entrada (para FIFO)
} Frame;
void print_frames(Frame *frames, int n) {
  printf("Marcos: ");
  for (int i = 0; i < n; i++) {
    if (frames[i].page == -1) printf("[-] ");
    else printf("[%d] ", frames[i].page);
  }
  printf("\n");
}

int main() {
  int references[PAGES] = {1, 2, 3, 4, 2, 1, 5, 3, 2, 4}; // Secuencia dereferencias
  Frame frames[FRAMES];
  int faults = 0, next_order = 0;
  // Inicializar marcos vacíos
  for (int i = 0; i < FRAMES; i++) {
    frames[i].page = -1;
    frames[i].order = 0;
  }
  printf("Simulación de FIFO con %d marcos:\n", FRAMES);
  for (int i = 0; i < PAGES; i++) {
    int page = references[i];
    int found = 0;
    // Verificar si la página ya está en memoria
    for (int j = 0; j < FRAMES; j++) {
      if (frames[j].page == page) {
        found = 1;
        break;
      }
    }
    if (!found) {
      // Buscar marco libre o reemplazar el más antiguo
      int oldest = 0;
      for (int j = 0; j < FRAMES; j++) {
        if (frames[j].page == -1) { // Marco libre
          frames[j].page = page;
          frames[j].order = next_order++;
          faults++;
          break;
        }
        if (frames[j].order < frames[oldest].order) 
          oldest = j;
      }
      //printf("NExt Order %d\n",next_order);
      if (faults <= FRAMES) continue; // No reemplazo aún

      // Reemplazar el más antiguo (FIFO)
      frames[oldest].page = page;
      frames[oldest].order = next_order++;
      faults++;
    }

    printf("Referencia %d: ", page);
    print_frames(frames, FRAMES);
  }
  printf("Total de fallos de página: %d\n", faults);
  return 0;
}
