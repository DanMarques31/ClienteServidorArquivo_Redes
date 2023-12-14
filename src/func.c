#include "func.h"

void envia_msg(const char *msg) {
    perror(msg);
    exit(1);
}