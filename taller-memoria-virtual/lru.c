#include <stdio.h>
#include <stdlib.h>
#define FRAMES 3
#define PAGES 10
typedef struct {
  int page; // Número de página
  int last_used; // Última vez que se usó
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
  int references[PAGES] = {1, 2, 3, 4, 2, 1, 5, 3, 2, 4};
  Frame frames[FRAMES];
  int faults = 0, time = 0;
  for (int i = 0; i < FRAMES; i++) {
    frames[i].page = -1;
    frames[i].last_used = 0;
  }
  printf("Simulación de LRU con %d marcos:\n", FRAMES);
  for (int i = 0; i < PAGES; i++) {
    int page = references[i];
    int found = 0;
    // Verificar si la página está en memoria
    for (int j = 0; j < FRAMES; j++) {
      if (frames[j].page == page) {
        found = 1;
        frames[j].last_used = time++; // Actualizar tiempo de uso
        break;
      }
    }
    if (!found) {
      int lru = 0;
      for (int j = 0; j < FRAMES; j++) {
        if (frames[j].page == -1) { // Marco libre
          frames[j].page = page;
          frames[j].last_used = time++;
          faults++;
          break;
        }
        if (frames[j].last_used < frames[lru].last_used) lru = j;
      }
      if (faults <= FRAMES) continue;
      // Reemplazar la menos recientemente usada
      frames[lru].page = page;
      frames[lru].last_used = time++;
      faults++;
    }
    printf("Referencia %d: ", page);
    print_frames(frames, FRAMES);
  }
  printf("Total de fallos de página: %d\n", faults);
  return 0;
}
