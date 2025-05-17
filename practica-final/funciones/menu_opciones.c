#include "funciones.h"
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
void MenuOpciones(IdValor *parametros){
  if (parametros==NULL) {
    perror("Error al pasar id de User");
    exit(-1);
  }
  int *idUser=parametros->id;
  int seleccion=-1;
  //system("clear");
  for (int i =0; funcionesMenu[i]!=NULL; i++) {
    printf("%d:%s\n", i+1,funcionesMenu[i]);
  }
  printf("Introduce la opcion de seleccion:\t");
  scanf("%d",&seleccion);
  switch (seleccion)
  {
    case 1:
      printf("%d\n",*((int *)parametros->valor));
      SacarDinero(idUser);
      break;
    case 2:
      printf("%d\n",*((int *)parametros->valor));
      MeterDinero(idUser);
      break;    
    case 3:
      printf("%d\n",*((int *)parametros->valor));
      ConsultarSaldo(idUser);
      break;
    case 4:
      printf("%d\n",*((int *)parametros->valor));
      InfoCuenta(idUser);
      break;
    case 5:
      printf("%d\n",*((int *)parametros->valor));
      Transaccion(idUser);
      break;
    case 6:
      printf("%d\n",*((int *)parametros->valor));
      PagarTasas(idUser);
      break;
    case 7:
      printf("%d\n",*((int *)parametros->valor));
      CancelarTarjeta(idUser);
      break;
    case 8:
      *((int *)parametros->valor)-=1;
      while ((Config.fd_escritura_cerrar = open(FIFO_CERRAR, O_WRONLY)) == -1) {
        perror("Banco: Error al abrir el FIFO para escritura. Intentando de nuevo...");
        sleep(1); // Esperar un poco antes de reintentar
      }
      int usuario=atoi(tabla->usuarios[*idUser-1].ncuenta);
      if (write(Config.fd_escritura_cerrar, &usuario, sizeof(int)) == -1) {
        perror("Banco: Error al escribir en el FIFO");
        break; // Salir del bucle si hay un error de escritura
      }
      EditarCsv(&tabla->usuarios[*idUser-1]);
      sem_unlink("/semaforo_dbcsv");
      sem_unlink("/semaforo_log");
      sem_unlink("/sem_log_trans");
      free(parametros->valor);
      exit(1);
      break;
    default:
      break;
  }
}
