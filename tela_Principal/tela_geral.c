#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

    //GERA OS NUMEROS ALEATORIOS PARA CADA PRODUTO
    srand(time(NULL));
    prod.cod_produto = rand() % 100; //GERA UM NÚMERO ENTRE 0 E 99
    
    int opcRetorno = 0;

    FILE *PRODUTO_CADASTRO;

    system("cls");

    printf("\n================================================================================================\n");
    printf("===================================TELA DE CADASTRO DE PRODUTO==================================\n");
    printf("================================================================================================\n");

    PRODUTO_CADASTRO = fopen("tela_cadastro.txt", "a+");

    if(PRODUTO_CADASTRO == NULL){
        printf("\nERRO!!\n");
        exit(1);
    }

    //PEDINDO PARA A PESSOA CADASTRAR O PRODUTO
    fflush(stdin); //LIMPA O BUFFER DE ENTRADA
    do{
        printf("\nDigite o nome do seu produto: ");
        fgets(prod.nome, 50, stdin);
        prod.nome[strcspn(prod.nome, "\n")] = '\0';

        if(!validaCharVazio(prod.nome)) {
            printf("Nome nao pode ser vazio!\n");
        }
    } while(!validaCharVazio(prod.nome));
    
    do {
        printf("\nDigite a categoria do produto: ");
        fgets(prod.categoria, 20, stdin);
        prod.categoria[strcspn(prod.categoria, "\n")] = '\0';

        if(!validaCharVazio(prod.categoria)) {
            printf("Categoria nao pode ser vazio!\n");
        }
    } while(!validaCharVazio(prod.categoria));
    
    do {
        printf("\nDigite a quantidade em estoque do produto: ");
        scanf("%d", &prod.quant_estoque);
        if(!validaQuantidade(prod.quant_estoque)) {
            printf("Quantidade estoque nao pode ser negativa!\n");
        }    
    } while(!validaQuantidade(prod.quant_estoque));
    
    fflush(stdin);
    do {
        printf("\nDigite a unidade de venda do produto(KG, LT, ...): ");
        fgets(prod.unid_venda, 4, stdin);
        prod.unid_venda[strcspn(prod.unid_venda, "\n")] = '\0';

        if(!validaCharVazio(prod.unid_venda)) {
            printf("Unidade de venda nao pode ser vazio!\n");
        }
    } while(!validaCharVazio(prod.unid_venda));
    
    do{ 
        printf("\nDigite o preco do produto em reais: ");
        scanf("%f", &prod.preco);

        if(!validaPreco(prod.preco)) {
            printf("Preco de venda nao pode ser menor que 1!\n");
        }

    } while(!validaPreco(prod.preco));

    printf("\n\nProduto cadastrado com sucesso!\n\n");

    printf("------------------------------------------------------------------------------------------\n");
    printf("Codigo    | Nome                | Categoria          | Qtde     | Unidade     | Preco   \n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("%-9d | %-19s | %-18s | %-8d | %-11s | %.2f\n",
            prod.cod_produto,
            prod.nome,
            prod.categoria,
            prod.quant_estoque,
            prod.unid_venda,
            prod.preco);
    printf("------------------------------------------------------------------------------------------\n");

    //ENVIANDO O CADASTRO PARA O ARQUIVO TXT
    fprintf(PRODUTO_CADASTRO, "\n%d, ", prod.cod_produto);
    fprintf(PRODUTO_CADASTRO, "%s, ", prod.nome);
    fprintf(PRODUTO_CADASTRO, "%s, ", prod.categoria);
    fprintf(PRODUTO_CADASTRO, "%d, ", prod.quant_estoque);
    fprintf(PRODUTO_CADASTRO, "%s, ", prod.unid_venda);
    fprintf(PRODUTO_CADASTRO, "%.2f", prod.preco);

    fclose(PRODUTO_CADASTRO);

    opcRetorno = retornoTela(opcRetorno);
    if (opcRetorno == 0) {
        main();
    }
    else {
        exit(0);
    }
}

void telaEntrada() {
    struct Entrada{
        int cod_entrada, cod_produto, quant_estoque;
        char nome[50], categoria[20], unid_venda[4];
        float preco;
    }entr;
    
    int opcRetorno = 0, contador = 0, quantidadeMaxima = 100, codigoComp, quantComp;
    char linha[200];

    FILE *PRODUTO_ENTRADA, *PRODUTO_CADASTRO;

    system("cls");

    printf("\n================================================================================================\n");
    printf("===================================TELA DE ENTRADA DE PRODUTO===================================\n");
    printf("================================================================================================\n");

    PRODUTO_ENTRADA = fopen("tela_entrada.txt", "a+");
    PRODUTO_CADASTRO = fopen("tela_cadastro.txt", "r");

    if(PRODUTO_ENTRADA == NULL) {
        printf("\nErro(Entrada)!\n");
        exit(1);
    }

    if(PRODUTO_CADASTRO == NULL) {
        printf("\nErro(Cadastro)!\n");
        exit(1);
    }

    printf("Digite o codigo do produto que deseja realizar a entrada:\n");
    scanf("%d", &codigoComp);

    while(fgets(linha, sizeof(linha), PRODUTO_CADASTRO) && contador < quantidadeMaxima) {
        if(sscanf(linha, "%d, %49[^,], %19[^,], %d, %3[^,], %f", &entr.cod_produto, entr.nome, entr.categoria, &entr.quant_estoque, entr.unid_venda, &entr.preco) == 6) {
            if(entr.cod_produto == codigoComp) {
                printf("\nProduto encontrado:\n");
                printf("--------------------------------------------------------\n");
                printf("Codigo | Nome                | Categoria          | Qtde     | Unidade | Preco   \n");
                printf("--------------------------------------------------------\n");
                printf("%-6d | %-17s | %-15s | %-9d | %-7s | %.2f\n",
                        entr.cod_produto,
                        entr.nome,
                        entr.categoria,
                        entr.quant_estoque,
                        entr.unid_venda,
                        entr.preco);
                printf("--------------------------------------------------------\n");
            }
            else {
                printf("Produto nao encontrado!");
            }
        }
        else {
            printf("Erro ao ler a linha: %s", linha);
        }
        contador++;
    }

    printf("Informe a quantidade que deseja adicionar em estoque para este produto:\n");
    scanf("%d", &quantComp);

    entr.quant_estoque = adicionaProduto(quantComp, entr.quant_estoque);

    printf("%d", entr.quant_estoque);

    fclose(PRODUTO_ENTRADA);
    fclose(PRODUTO_CADASTRO);
    
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