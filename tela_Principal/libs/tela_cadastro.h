#ifndef tela_cadastro
#define tela_cadastro

#include <stdbool.h>

bool validaQuantidade(int quantidade) {
    return (quantidade >= 0);
}

bool validaCharVazio(char campChar[]) {
    return (campChar != NULL && strlen(campChar) > 0);
}

bool validaPreco(float preco) {
    return (preco >= 1);
}

#endif