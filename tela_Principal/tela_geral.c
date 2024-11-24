#include <stdio.h>
#include <stdlib.h>

//importação das bibliotecas
#include "../tela_Principal/libs/tela_cadastro.h"
#include "../tela_Principal/libs/tela_entrada.h"
#include "../tela_Principal/libs/tela_saida.h"
#include "../tela_Principal/libs/tela_venda.h"
#include "../tela_Principal/libs/tela_entrega.h"
#include "../tela_Principal/libs/tela_pesquisa.h"

void telaCadastro();
void telaEntrada();
void telaSaida();
void telaVenda();
void telaEntrega();
void telaPesquisa();
int retornoTela();

int main() {
    int opcEscolha;

    system("cls");

    printf("************************************************************************************************\n");
    printf("***************************************** SHELLMANAGER *****************************************\n");
    printf("************************************************************************************************\n");
    printf("***************************** SISTEMA DE GESTAO DE ESTOQUE E VENDA *****************************\n");
    printf("************************************************************************************************\n");

    printf("\n================================================================================================\n");
    printf("=========================================TELA PRINCIPAL=========================================\n");
    printf("================================================================================================\n");

    printf("MENU:\n");
    printf("1 - CADASTRO DE PRODUTOS\n");
    printf("2 - ENTRADA DE PRODUTOS\n");
    printf("3 - SAIDA DE PRODUTOS\n");
    printf("4 - VENDAS\n");
    printf("5 - Entregas\n");
    printf("6 - PESQUISA DE PRODUTOS\n");

    printf("Qual tela deseja acessar? (Digite apenas o numero da opcao)\n");
    scanf("%d", &opcEscolha);

    switch (opcEscolha) {
        case 1:
            telaCadastro();
            break;
        case 2:
            telaEntrada();
            break;
        case 3:
            telaSaida();
            break;
        case 4:
            telaVenda();
            break;
        case 5:
            telaEntrega();
            break;
        case 6:
            telaPesquisa();
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
    }

    return 0;
}

void telaCadastro() {
    int opcRetorno = 0;

    system("cls");

    printf("\n================================================================================================\n");
    printf("===================================TELA DE CADASTRO DE PRODUTO==================================\n");
    printf("================================================================================================\n");

    //INSIRA O CODIGO APARTIR DAQUI DECLARANDO A VARIAVEL JUNTO DA VARIAVEL ACIMA


    opcRetorno = retornoTela(opcRetorno);
    if (opcRetorno == 0) {
        main();
    }
    else {
        exit(0);
    }
}

void telaEntrada() {
    int opcRetorno = 0;

    system("cls");

    printf("\n================================================================================================\n");
    printf("===================================TELA DE ENTRADA DE PRODUTO===================================\n");
    printf("================================================================================================\n");

    //INSIRA O CODIGO APARTIR DAQUI DECLARANDO A VARIAVEL JUNTO DA VARIAVEL ACIMA


    opcRetorno = retornoTela(opcRetorno);
    if (opcRetorno == 0) {
        main();
    }
    else {
        exit(0);
    }
}

void telaSaida() {
    int opcRetorno = 0;

    system("cls");

    printf("\n================================================================================================\n");
    printf("====================================TELA DE SAIDA DE PRODUTO====================================\n");
    printf("================================================================================================\n");

    //INSIRA O CODIGO APARTIR DAQUI DECLARANDO A VARIAVEL JUNTO DA VARIAVEL ACIMA


    opcRetorno = retornoTela(opcRetorno);
    if (opcRetorno == 0) {
        main();
    }
    else {
        exit(0);
    }
}

void telaVenda() {
    int opcRetorno = 0;

    system("cls");

    printf("\n================================================================================================\n");
    printf("=========================================TELA DE VENDAS=========================================\n");
    printf("================================================================================================\n");

    //INSIRA O CODIGO APARTIR DAQUI DECLARANDO A VARIAVEL JUNTO DA VARIAVEL ACIMA


    opcRetorno = retornoTela(opcRetorno);
    if (opcRetorno == 0) {
        main();
    }
    else {
        exit(0);
    }
}

void telaEntrega() {
    int opcRetorno = 0;

    system("cls");

    printf("\n================================================================================================\n");
    printf("================================TELA DE ENTREGAS DE MERCADORIA==================================\n");
    printf("================================================================================================\n");

    //INSIRA O CODIGO APARTIR DAQUI DECLARANDO A VARIAVEL JUNTO DA VARIAVEL ACIMA


    opcRetorno = retornoTela(opcRetorno);
    if (opcRetorno == 0) {
        main();
    }
    else {
        exit(0);
    }
}

void telaPesquisa() {
    int opcRetorno = 0;

    system("cls");

    printf("\n================================================================================================\n");
    printf("=================================TELA DE PESQUISA DE PRODUTO====================================\n");
    printf("================================================================================================\n");

    //INSIRA O CODIGO APARTIR DAQUI DECLARANDO A VARIAVEL JUNTO DA VARIAVEL ACIMA


    opcRetorno = retornoTela(opcRetorno);
    if (opcRetorno == 0) {
        main();
    }
    else {
        exit(0);
    }
}


int retornoTela(int opcSaida) {
    char escolha;

    do {
        printf("\nDeseja voltar a tela principal? (S/N): ");
        scanf(" %c", &escolha);

        if(escolha == 'S' || escolha == 's') {
            return  opcSaida = 0;
        } else if(escolha == 'N' || escolha == 'n') {
            return opcSaida = 1;
        } else {
            printf("Opção invalida, digite novamente!\n");
        }  
    } while(escolha != 'S' && escolha != 's' && escolha != 'N' && escolha != 'n');

    return opcSaida;
}