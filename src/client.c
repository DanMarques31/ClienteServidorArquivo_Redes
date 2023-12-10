#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    
    if (argc != 5) {
        fprintf(stderr, "Uso: %s <host_do_servidor> <porta_servidor> <nome_arquivo> <tam_buffer>\n", argv[0]);
        exit(1);
    }

    char *server_host = argv[1];
    int porta_servidor = atoi(argv[2]);
    char *nome_arquivo = argv[3];
    int tam_buffer = atoi(argv[4]);

    int sockfd = conectarAoServidor(server_host, porta_servidor);

    enviarString(sockfd, nome_arquivo);

    FILE *arquivo = abrirArquivo(nome_arquivo, "w+");

    if (arquivo == NULL)
        mensagemErro("Erro ao abrir arquivo");

    struct timeval inicio, fim;
    gettimeofday(&inicio, NULL);

    receberArquivo(sockfd, arquivo, tam_buffer);

    fecharArquivo(arquivo);
    fecharConexao(sockfd);

    gettimeofday(&fim, NULL);
    calcularEImprimirResultado(tam_buffer, obterTamanhoArquivo(nome_arquivo), inicio, fim);

    return 0;
}
