#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define SHM_SIZE sizeof(int)
int main(int argc, char *argv[]) {
  key_t key = ftok("shmfile", 65); // Genera una clave única
  int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // Crea memoria compartida
  if (shmid == -1) { perror("shmget"); exit(1); }
    int *counter = shmat(shmid, NULL, 0); // Adjunta la memoria
  if (counter == (int *)-1) { perror("shmat"); exit(1); }
    int is_writer = (argc > 1 && argv[1][0] == 'w');
  if (is_writer) {
    *counter = 0;
    for (int i = 0; i < 5; i++) {
      printf("Escritor: %d\n", ++(*counter));

      sleep(1);
    }
  } else {
    for (int i = 0; i < 5; i++) {
      printf("Lector: %d\n", *counter);
      sleep(1);
    }
  }
  shmdt(counter); // Desadjunta la memoria
  if (is_writer) shmctl(shmid, IPC_RMID, NULL); // Elimina la memoria (solo escritor)
  return 0;
}
