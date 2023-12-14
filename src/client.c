#include "func.h"

int main(int argc, char *argv[]) {
    
    if (argc != 5) {
        fprintf(stderr, "Argumentos que devem ser passados: %s host_do_servidor porta_servidor nome_arquivo_entrada tam_buffer\n", argv[0]);
        exit(1);
    }

    const char *host_servidor = argv[1];
    int porta_servidor = atoi(argv[2]);
    const char *arquivo_entrada = argv[3];
    int tam_buffer = atoi(argv[4]);

    int sock_descritor = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock_descritor < 0) {
        envia_msg("Erro ao abrir socket");
    }

    struct sockaddr_in endereco;
    bzero((char *)&endereco, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(porta_servidor);
    inet_pton(AF_INET, host_servidor, &endereco.sin_addr);

    struct timeval inicio_tempo, final_tempo;
    gettimeofday(&inicio_tempo, NULL);

    if (connect(sock_descritor, (struct sockaddr *)&endereco, sizeof(endereco)) < 0) {
        envia_msg("Problema ao conectar");
    }

    send(sock_descritor, arquivo_entrada, strlen(arquivo_entrada) + 1, 0);

    FILE *arquivo = fopen("saida.txt", "w+");
    if (!arquivo) {
        envia_msg("Erro ao abrir o arquivo de saída.");
    }
    
    char buffer[TAM_BUFFER];
    int bytes_recebidos, total_bytes_recebidos = 0;

    while ((bytes_recebidos = recv(sock_descritor, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, bytes_recebidos, arquivo);
        total_bytes_recebidos += bytes_recebidos;
    }

    fclose(arquivo);
    close(sock_descritor);

    gettimeofday(&final_tempo, NULL);

    double tempo_passado = (final_tempo.tv_sec - inicio_tempo.tv_sec) + (final_tempo.tv_usec - inicio_tempo.tv_usec) / 1e6;
    double taxa_transferencia = total_bytes_recebidos / (tempo_passado * 1000);

    printf("Buffer: %5d byte(s); total de bytes recebidos: %d.\n", tam_buffer, total_bytes_recebidos);
    printf("Tempo total de execução: %.6f segundos.\n", tempo_passado);
    printf("Taxa de Transferência: %10.2f kbps.\n", taxa_transferencia);

    return 0;
}
