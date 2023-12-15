#include <stdio.h> // Entrada e saida padrão do C
#include <stdlib.h> // Alocação e controle de processos
#include <string.h> // Manipulação de string
#include <sys/socket.h> // Programação em socket
#include <netinet/in.h> // Estruturas do protocolo IP
#include <unistd.h> // Funções do sistema
#include <arpa/inet.h> // Manipulação de endereço IP em string
#include <sys/time.h> // Funções relacionadas a tempo
#include <math.h> // Funções matemáticas

#define TAM_BUFFER 65536 // Valor máximo de buffer

// Assinaturas das funções
void envia_msg(const char *msg);
void calcular_e_imprimir_tempos(struct timeval *inicio, struct timeval *final, int total_bytes, int tam_buffer);