#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <math.h>

#define TAM_BUFFER 65536

void envia_msg(const char *msg);
void calcular_e_imprimir_tempos(struct timeval *inicio, struct timeval *final, int total_bytes, int tam_buffer);