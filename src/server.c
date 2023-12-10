#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <porta_servidor> <tam_buffer>\n", argv[0]);
        exit(1);
    }

    int porta_servidor = atoi(argv[1]);
    int tam_buffer = atoi(argv[2]);

    int sockfd = iniciarServidor(porta_servidor);

    int newsockfd = aguardarConexao(sockfd);

    char arquivo[MAX_BUFFER];
    receberString(newsockfd, arquivo);

    FILE *arquivoFD = abrirArquivo(arquivo, "r");

    if (arquivoFD == NULL) {
        fecharConexao(newsockfd);
        fecharConexao(sockfd);
        mensagemErro("Erro ao abrir arquivo");
    }

    struct timeval inicio, fim;
    gettimeofday(&inicio, NULL);

    enviarArquivo(newsockfd, arquivoFD, tam_buffer);

    fecharArquivo(arquivoFD);
    fecharConexao(newsockfd);
    fecharConexao(sockfd);

    gettimeofday(&fim, NULL);
    calcularEImprimirResultado(tam_buffer, obterTamanhoArquivo(arquivo), inicio, fim);

    return 0;
}
