#ifndef FUNC_H
#define FUNC_H

#define MAX_BUFFER 1024

void mensagemErro(char *mensagem);
int conectarAoServidor(char *server_host, int porta_servidor);
void receberArquivo(int sockfd, char *arquivo, int tam_buffer);
void calcularEImprimirResultado(int tam_buffer, int bytes_recebidos, struct timeval inicio, struct timeval fim);

#endif