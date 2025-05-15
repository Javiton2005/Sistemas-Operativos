#include "funciones.h"
#include <stdio.h>
void MenuOpciones(int *idUser){
  if (idUser==NULL) {
    perror("Error al pasar id de User");
    exit(-1);
  }
  int seleccion=-1;
  system("clear");
  for (int i =0; funcionesMenu[i]!=NULL; i++) {
    printf("%d:%s\n", i+1,funcionesMenu[i]);
  }
  printf("Introduce la opcion de seleccion:\t");
  scanf("%d",&seleccion);
  switch (seleccion)
  {
    case 1:
      SacarDinero(idUser);
      break;
    case 2:
      MeterDinero(idUser);
      break;    
    case 3:
      ConsultarSaldo(idUser);
      break;
    case 4:
      InfoCuenta(idUser);
      break;
    case 5:
      Transaccion(idUser);
      break;
    case 6:
      PagarTasas(idUser);
      break;
    case 7:
      CancelarTarjeta(idUser);
      break;
    case 8:
      while ((Config.fd_escritura_cerrar = open(FIFO_CERRAR, O_WRONLY)) == -1) {
        perror("Banco: Error al abrir el FIFO para escritura. Intentando de nuevo...");
        sleep(1); // Esperar un poco antes de reintentar
      }
      printf("%d",atoi(tabla->usuarios[*idUser-1].ncuenta));

      while (getchar()!='\n') {
      
      }
      getchar();
      int usuario=atoi(tabla->usuarios[*idUser-1].ncuenta);
      if (write(Config.fd_escritura_cerrar, &usuario, sizeof(int)) == -1) {
        perror("Banco: Error al escribir en el FIFO");
        break; // Salir del bucle si hay un error de escritura
      }
      sem_unlink("/semaforo_dbcsv");
      sem_unlink("/semaforo_log");
      sem_unlink("/sem_log_trans");
      exit(1);
      break;
    default:
      break;
  }
}
