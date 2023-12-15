#include "func.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso apropriado para instanciar servidor: %s porta_servidor tam_buffer\n", argv[0]);
        exit(1);
    }

    int porta_servidor = atoi(argv[1]);
    int tam_buffer = atoi(argv[2]);

    int sock_descritor = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock_descritor < 0) {
        envia_msg("Erro ao abrir socket de conexão.");
    }
    
    int reusar_porta = 1;
    setsockopt(sock_descritor, SOL_SOCKET, SO_REUSEADDR, &reusar_porta, sizeof(reusar_porta));

    struct sockaddr_in endereco_server, endereco_client;
    bzero((char *)&endereco_server, sizeof(endereco_server));
    endereco_server.sin_family = AF_INET;
    endereco_server.sin_port = htons(porta_servidor);
    endereco_server.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock_descritor, (struct sockaddr *)&endereco_server, sizeof(endereco_server)) < 0) {
        envia_msg("Problema ao anexar.");
    }
    
    listen(sock_descritor, 10);

    socklen_t client_len = sizeof(endereco_client);
    int sock_descritor2 = accept(sock_descritor, (struct sockaddr *)&endereco_client, &client_len);
    if (sock_descritor2 < 0) {
        envia_msg("Erro ao aceitar conexão.");
    }
    
    struct timeval inicio_tempo, final_tempo;
    gettimeofday(&inicio_tempo, NULL);

    char arquivo_entrada[1024];
    recv(sock_descritor2, arquivo_entrada, sizeof(arquivo_entrada), 0);

    FILE *arquivo = fopen(arquivo_entrada, "r");
    if (!arquivo) {
        envia_msg("Erro ao abrir arquivo.");
        close(sock_descritor2);
        close(sock_descritor);
        exit(1);
    }

    char buffer[tam_buffer];
    int bytes_lidos = 0;
    int bytes_enviados = 0;

    while ((bytes_lidos = fread(buffer, 1, sizeof(buffer), arquivo)) > 0) {
        send(sock_descritor2, buffer, bytes_lidos, 0);
        bytes_enviados += bytes_lidos;
    }

    fclose(arquivo);
    close(sock_descritor2);
    close(sock_descritor);

    gettimeofday(&final_tempo, NULL);

    calcular_e_imprimir_tempos(&inicio_tempo, &final_tempo, bytes_enviados, tam_buffer);

    return 0;
}
