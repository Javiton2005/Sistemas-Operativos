#include <stdio.h>
#define MARCO 3
#define PAGES 10

typedef struct{
  int page;
  int entrada;
} FRAME;

void print_frames(FRAME *frames, int n) {
  printf("Marcos: ");
  for (int i = 0; i < n; i++) {
    if (frames[i].page == -1) printf("[-] ");
    else printf("[%d] ", frames[i].page);
  }
  printf("\n");
}
int comprobarUltimo(FRAME *frames, int n){
  int menor=frames[0].entrada;
  int menorIndex=0;
  for (int i=0; i<n ; i++) {
    if(frames[i].entrada<menor){
      menor=frames[i].entrada;
      menorIndex=i;
    }
  }
  return menorIndex;
}
int main(int argc, char *argv[]){
  int lista[PAGES]={1,2,3,4,2,1,5,3,2,4};
  FRAME marcos[MARCO];
  int faltas=0;


  for (int i =0; i<MARCO; i++) {
    marcos[i].page=-1;
    marcos[i].entrada=0;
  }

  for (int i = 0; i<PAGES; i++) {
    int encontrado=0;
    for (int j=0; j<MARCO; j++) {
      if (lista[i]==marcos[j].page) {
        encontrado=1;
        break; 
      }
    }
    if (!encontrado) {
      int asignado=0;
      for (int j=0; j<MARCO; j++) {
        if(marcos[j].page==-1){
          marcos[j].page=lista[i];
          marcos[j].entrada=i;
          asignado++;
          faltas++;
          break;
        }
      }
      if(!asignado){
        int ultimo=comprobarUltimo(marcos, MARCO);
        marcos[ultimo].page=lista[i];
        marcos[ultimo].entrada=i;
      }
    }
    print_frames(marcos, MARCO);
  }

  

  return 1;
}
