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
    
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <porta_servidor> <tam_buffer>\n", argv[0]);
        exit(1);
    }

    int porta_servidor = atoi(argv[1]);
    int tam_buffer = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        mensagemErro("Erro ao abrir socket");
    }

    struct sockaddr_in serv_addr, cli_addr;
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(porta_servidor);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        mensagemErro("Erro ao fazer bind");
    }
       
    listen(sockfd, 5);

    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    
    if (newsockfd < 0) {
        mensagemErro("Erro ao aceitar conexão");
    }

    char fileTest[MAX_BUFFER];
    recv(newsockfd, fileTest, MAX_BUFFER, 0);

    FILE *arquivo = fopen(fileTest, "r");
    if (arquivo == NULL) {
        close(newsockfd);
        close(sockfd);
        mensagemErro("Erro ao abrir arquivo");
    }

    struct timeval inicio, fim;
    gettimeofday(&inicio, NULL);

    char buffer[MAX_BUFFER];
    int bytes_enviados = 0;

    while (1) {
        
        int bytes = fread(buffer, 1, tam_buffer, arquivo);
        if (bytes <= 0)
            break;

        send(newsockfd, buffer, bytes, 0);
        bytes_enviados += bytes;
    }

    fclose(arquivo);
    close(newsockfd);
    close(sockfd);

    gettimeofday(&fim, NULL);
    double tempo_gasto = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1e6;

    printf("Nome do arquivo: %s, Bytes enviados: %u\n", fileTest, bytes_enviados);

    return 0;
}
