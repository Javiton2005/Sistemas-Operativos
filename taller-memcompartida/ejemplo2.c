#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/my_shared_memory"
#define SHM_SIZE_INITIAL sizeof(int)
#define SHM_SIZE_EXPANDED (SHM_SIZE_INITIAL * 2)

int main() {
  int shm_fd;
  void *shm_ptr;
  // Crear memoria compartida
  shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, SHM_SIZE_INITIAL);
  // Mapear tamaño inicial
  shm_ptr = mmap(0, SHM_SIZE_INITIAL, PROT_WRITE | PROT_READ, MAP_SHARED,
  shm_fd, 0);
  *(int *)shm_ptr = 42;
  printf("Valor inicial: %d\n", *(int *)shm_ptr);
  // Ampliar tamaño
  ftruncate(shm_fd, SHM_SIZE_EXPANDED);
  munmap(shm_ptr, SHM_SIZE_INITIAL); // Desmapear primero
  shm_ptr = mmap(0, SHM_SIZE_EXPANDED, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
  printf("Valor tras ampliar: %d\n", *(int *)shm_ptr);
  // Limpiar
  munmap(shm_ptr, SHM_SIZE_EXPANDED);
  close(shm_fd);
  shm_unlink(SHM_NAME);
  return 0;
}
