#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    struct Produto {
        int cod_produto, quant_estoque;
        char nome[50], categoria[20], unid_venda[4];
        float preco;
    }prod;
    
    int opcRetorno = 0;

    FILE *PRODUTO;

    system("cls");

    printf("\n================================================================================================\n");
    printf("===================================TELA DE CADASTRO DE PRODUTO==================================\n");
    printf("================================================================================================\n");

    //INSIRA O CODIGO APARTIR DAQUI DECLARANDO A VARIAVEL JUNTO DA VARIAVEL ACIMA

    PRODUTO = fopen("tela_cad.txt", "a+");

    if(PRODUTO == NULL){
        printf("\nERRO!!\n");
    }

    getchar();
    printf("\nDigite o nome do seu produto: ");
    fgets(prod.nome, 50, stdin);
    printf("\nDigite a categoria do produto: ");
    fgets(prod.categoria, 20, stdin);
    printf("\nDigite a qunatidade em estoque do produto: ");
    scanf("%d", &prod.quant_estoque);
    getchar();
    printf("\nDigite a unidade de venda do produto(KG, LT, ...): ");
    fgets(prod.unid_venda, 4, stdin);
    printf("\nDigite o preco do produto em reais: ");
    scanf("%f", &prod.preco);

    fprintf(PRODUTO, "\n\n\nO codigo do produto: %d\n\n", prod.cod_produto);
    fprintf(PRODUTO, "Nome do produto: %s\n", prod.nome);
    fprintf(PRODUTO, "A categoria do produto: %s\n", prod.categoria);
    fprintf(PRODUTO, "A quntidade do produto em estoque: %d\n\n", prod.quant_estoque);
    fprintf(PRODUTO, "A unidade de venda do produto: %s\n", prod.unid_venda);
    fprintf(PRODUTO, "O preco do produto: %.2f\n\n", prod.preco);

    fclose(PRODUTO);

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
            printf("Opcao invalida, digite novamente!\n");
        }  
    } while(escolha != 'S' && escolha != 's' && escolha != 'N' && escolha != 'n');

    return opcSaida;
}