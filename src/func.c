#include "func.h"

// Função que envia qualquer mensagem de erro do programa
void envia_msg(const char *msg) {
    perror(msg);
    exit(1);
}

// Função que calcula e imprime os tempos e as métricas
void calcular_e_imprimir_tempos(struct timeval *inicio, struct timeval *final, int total_bytes, int tam_buffer) {

    double tempo_passado = (final->tv_sec - inicio->tv_sec) + (final->tv_usec - inicio->tv_usec) / 1e6;
    double taxa_transferencia = total_bytes / (tempo_passado * 1000);

    printf("Tempo total de execução: %.6f segundos.\n", tempo_passado);
    printf("Taxa de Transferência: %10.2f kbps.\n", taxa_transferencia);
    printf("Tamanho do buffer eh %5d byte(s), número total de bytes enviados: %d.\n", tam_buffer, total_bytes);

}