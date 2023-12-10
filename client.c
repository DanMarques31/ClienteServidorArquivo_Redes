#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

#define MAX_BUFFER 1024

void mensagemErro(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    
    if (argc != 5) {
        fprintf(stderr, "Uso: %s <host_do_servidor> <porta_servidor> <nome_arquivo> <tam_buffer>\n", argv[0]);
        exit(1);
    }

    char *hostname = argv[1];
    int porta_servidor = atoi(argv[2]);
    char *nome_arquivo = argv[3];
    int tam_buffer = atoi(argv[4]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        mensagemErro("Erro ao abrir socket");
    }

    struct sockaddr_in serv_addr;
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(porta_servidor);
    inet_pton(AF_INET, hostname, &(serv_addr.sin_addr));

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        mensagemErro("Erro ao conectar");
    }

    send(sockfd, nome_arquivo, strlen(nome_arquivo), 0);

    FILE *arquivo = fopen(nome_arquivo, "w+");
    
    if (arquivo == NULL) {
        mensagemErro("Erro ao abrir arquivo");
    }

    struct timeval inicio, fim;
    gettimeofday(&inicio, NULL);

    char buffer[MAX_BUFFER];
    int bytes_recebidos = 0;

    while (1) {
        int bytes = recv(sockfd, buffer, tam_buffer, 0);
        
        if (bytes <= 0)
            break;

        fwrite(buffer, 1, bytes, arquivo);
        bytes_recebidos += bytes;
    }

    fclose(arquivo);
    close(sockfd);

    gettimeofday(&fim, NULL);
    double tempo_gasto = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1e6;
    double velocidade = (bytes_recebidos * 8) / (tempo_gasto * 1000);

    printf("Buffer = %5u byte(s), %10.2f kbps (%u bytes em %.6f s)\n", tam_buffer, velocidade, bytes_recebidos, tempo_gasto);

    return 0;
}
