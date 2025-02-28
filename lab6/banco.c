#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <threads.h>
#include <unistd.h>
#include <string.h>
int fd[2];

void manejador() {
  int dinero_prueba;
  read(fd[0], &dinero_prueba, sizeof(dinero_prueba));
  printf("Esto imprime algo");
  if(dinero_prueba>10)
    printf("Es una cantidad de millonarios->%d\n",dinero_prueba);
  close(fd[0]);
}
int main(int argc, char *argv[]){
  int pid;
  int dinero;
  int fd[2];
  pipe(fd);
  close(fd[0]);
  while (true) {
    scanf("%d", &dinero);
    write(fd[1], &dinero, sizeof(dinero));
    signal(SIGUSR1, manejador);
    close(fd[1]);
  }
  return 1;
}
