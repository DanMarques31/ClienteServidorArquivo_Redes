#include "func.h"

int main(int argc, char *argv[]) {
    
    // verifica o número de argumentos
    if (argc != 5) {
        fprintf(stderr, "Argumentos que devem ser passados: %s host_do_servidor porta_servidor nome_arquivo_entrada tam_buffer\n", argv[0]);
        exit(1);
    }

    // Pega os argumentos da linha de comando
    const char *host_servidor = argv[1];
    int porta_servidor = atoi(argv[2]);
    const char *arquivo_entrada = argv[3];
    int tam_buffer = atoi(argv[4]);

    // Cria socket para o server e verifica erro 
    int sock_descritor = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_descritor < 0) {
        envia_msg("Erro ao abrir socket");
    }

    // Configura adress do server
    struct sockaddr_in endereco;
    bzero((char *)&endereco, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(porta_servidor);
    inet_pton(AF_INET, host_servidor, &endereco.sin_addr);

    // Cria e chama a função de contagem de tempo
    struct timeval inicio_tempo, final_tempo;
    gettimeofday(&inicio_tempo, NULL);

    // Conecta no server
    if (connect(sock_descritor, (struct sockaddr *)&endereco, sizeof(endereco)) < 0) {
        envia_msg("Problema ao conectar");
    }

    // Envia o nome do arquivo para o server
    send(sock_descritor, arquivo_entrada, strlen(arquivo_entrada) + 1, 0);

    // Abre o arquivo de saida "saida.txt"
    FILE *arquivo = fopen("saida.txt", "w+");
    if (!arquivo) {
        envia_msg("Erro ao abrir o arquivo de saída.");
    }
    
    // Variaveis para receber os dados do server e escrever no saida.txt
    char buffer[TAM_BUFFER];
    int bytes_recebidos, total_bytes_recebidos = 0;

    while ((bytes_recebidos = recv(sock_descritor, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, bytes_recebidos, arquivo);
        total_bytes_recebidos += bytes_recebidos;
    }

    // Fecha arquivo e socket
    fclose(arquivo);
    close(sock_descritor);

    // Termina contagem do tempo e chama função que calcula e imprime as métricas
    gettimeofday(&final_tempo, NULL);
    calcular_e_imprimir_tempos(&inicio_tempo, &final_tempo, total_bytes_recebidos, tam_buffer);

    return 0;
}
