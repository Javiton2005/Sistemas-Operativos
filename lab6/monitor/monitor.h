#ifndef MONITOR_H
#define MONITOR_H

#include "../comun/comun.h"

void monitor(int fd_alerta);

void *registrar_anomalia(int codigo_anomalia);
void *hilo_fondos_insuficientes(void *arg);
void *hilo_transacciones_grandes(void *arg);
void *hilo_login_fallido(void *arg);
void *hilo_transacciones_internacionales(void *arg);
void *hilo_secuencia_inusual(void *arg);

#endif // MONITOR_H