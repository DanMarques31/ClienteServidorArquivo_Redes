#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

void mensagemErro(char *mensagem) {
    perror(mensagem);
    exit(1);
}

int conectarAoServidor(char *server_host, int porta_servidor) {
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        mensagemErro("Erro ao abrir socket");
    }

    struct sockaddr_in serv_addr;
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(porta_servidor);
    inet_pton(AF_INET, server_host, &(serv_addr.sin_addr));

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        mensagemErro("Erro ao conectar");
    }

    return sockfd;
}

void receberArquivo(int sockfd, char *arquivo, int tam_buffer) {
    
    FILE *arquivoFD = fopen(arquivo, "w+");
    
    if (arquivoFD == NULL) {
        mensagemErro("Erro ao abrir arquivo");
    }

    char buffer[MAX_BUFFER];
    int bytes_recebidos = 0;

    while (1) {
        
        int bytes = recv(sockfd, buffer, tam_buffer, 0);
        
        if (bytes <= 0)
            break;

        fwrite(buffer, 1, bytes, arquivoFD);
        bytes_recebidos += bytes;
    }

    fclose(arquivoFD);
}

void calcularEImprimirResultado(int tam_buffer, int bytes_recebidos, struct timeval inicio, struct timeval fim) {

    double tempo_gasto = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1e6;
    double velocidade = (bytes_recebidos * 8) / (tempo_gasto * 1000);

    printf("Buffer = %5u byte(s), %10.2f kbps (%u bytes em %.6f s)\n", tam_buffer, velocidade, bytes_recebidos, tempo_gasto);
}