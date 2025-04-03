#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#define SHM_NAME "/my_shared_memory"
#define SHM_SIZE sizeof(int)

int main(int argc, char *argv[]) {
  int shm_fd;
  int *counter;
  int is_writer = (argc > 1 && argv[1][0] == 'w');
  // Abrir o crear memoria compartida
  shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1) { perror("shm_open"); exit(1); }
    // Ajustar tamaño
    ftruncate(shm_fd, SHM_SIZE);
    // Mapear memoria
    counter = mmap(0, SHM_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    if (counter == MAP_FAILED) { perror("mmap"); exit(1); }
    if (is_writer) {
      *counter = 0;
      for (int i = 0; i < 5; i++) {
        printf("Escritor: contador = %d\n", ++(*counter));
        sleep(1);
      }
    } 
    else {
    for (int i = 0; i < 5; i++) {
      printf("Lector: contador = %d\n", *counter);
      sleep(1);
    }
  }
  // Desmapear memoria
  munmap(counter, SHM_SIZE);
  close(shm_fd);
  if (is_writer) shm_unlink(SHM_NAME); // Solo el escritor elimina el objeto
  return 0;
}
