#ifndef tela_saida
#define tela_saida

#include <stdbool.h>

int removeProduto(int quantidade_adc, int quantidade) {
    return quantidade - quantidade_adc;
}

bool validaQuantidadeSaida(int quantidade) {
    return (quantidade >= 0);
}

bool verificaTotSaida(int quantidadeDigit, int quantidadeEstoque) {
    return (quantidadeEstoque - quantidadeDigit) >= 0;
}

#endif