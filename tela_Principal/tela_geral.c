#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//importação das bibliotecas
#include "../tela_Principal/libs/tela_cadastro.h"
#include "../tela_Principal/libs/tela_entrada.h"
#include "../tela_Principal/libs/tela_saida.h"

void telaCadastro();
void telaEntrada();
void telaSaida();
void telaVenda();
void telaEntrega();
void telaPesquisa();
int retornoTela();
void configuracao();

int main() {
    int opcEscolha, opcRetorno;

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
    printf("5 - ENTREGAS\n");
    printf("6 - PESQUISA DE PRODUTOS\n");
    printf("7 - CONFIGURACAO\n");
    printf("8 - SAIR\n");

    do {
        opcRetorno = 0;
        printf("Qual tela deseja acessar? (Digite apenas o numero da opcao)\n");
        scanf("%d", &opcEscolha);

        while (getchar() != '\n'); 
        
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
            case 7:
                configuracao();
                break;
            case 8:
                exit(1);
            default:
                opcRetorno = 1;
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcRetorno == 1);
    
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
    fflush(stdin);
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
    fprintf(PRODUTO_CADASTRO, "%d, ", prod.cod_produto);
    fprintf(PRODUTO_CADASTRO, "%s, ", prod.nome);
    fprintf(PRODUTO_CADASTRO, "%s, ", prod.categoria);
    fprintf(PRODUTO_CADASTRO, "%d, ", prod.quant_estoque);
    fprintf(PRODUTO_CADASTRO, "%s, ", prod.unid_venda);
    fprintf(PRODUTO_CADASTRO, "%.2f\n", prod.preco);

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
        int cod_entrada, cod_produto, quant_estoque, quant_anterior;
        char nome[50], categoria[20], unid_venda[4];
        float preco;
    }entr, produto[100];

    //GERA OS NUMEROS ALEATORIOS PARA CADA PRODUTO
    srand(time(NULL));
    entr.cod_entrada = rand() % 100; //GERA UM NÚMERO ENTRE 0 E 99
    
    int opcRetorno = 0, contador = 0, quantidadeMaxima = 100, codigoComp, quantComp, prodEnc = 0;
    char linha[200];

    FILE *PRODUTO_ENTRADA, *PRODUTO_CADASTRO, *ARQUIVO_TEMP_CADASTRO;

    system("cls");

    printf("\n================================================================================================\n");
    printf("===================================TELA DE ENTRADA DE PRODUTO===================================\n");
    printf("================================================================================================\n");

    PRODUTO_ENTRADA = fopen("tela_entrada.txt", "a+");
    PRODUTO_CADASTRO = fopen("tela_cadastro.txt", "r");
    ARQUIVO_TEMP_CADASTRO = fopen("arquivo_temp_cadastro.txt", "a+");

    if(PRODUTO_ENTRADA == NULL) {
        printf("\nErro(Entrada)!\n");
        exit(1);
    }

    if(PRODUTO_CADASTRO == NULL) {
        printf("\nErro(Cadastro)!\n");
        exit(1);
    }

    if(ARQUIVO_TEMP_CADASTRO == NULL) {
        printf("\nErro(Arquivo temporario)!");
        exit(1);
    }

    while(fgets(linha, sizeof(linha), PRODUTO_CADASTRO) && contador < quantidadeMaxima) {
        if(sscanf(linha, "%d, %49[^,], %19[^,], %d, %3[^,], %f", &entr.cod_produto, entr.nome, entr.categoria, &entr.quant_estoque, entr.unid_venda, &entr.preco) == 6) {
            produto[contador] = entr;
            contador++;   
        }
        else {
            printf("Erro ao ler a linha: %s", linha);
        }
    }

    do {
        fflush(stdin);
        printf("Digite o codigo do produto que deseja realizar a entrada:\n");
        scanf("%d", &codigoComp);

        for(int i = 0; i < contador; i++) {
            if(produto[i].cod_produto == codigoComp) {
                printf("\nProduto encontrado:\n");
                printf("------------------------------------------------------------------------------------------\n");
                printf("Codigo    | Nome                | Categoria          | Qtde     | Unidade     | Preco   \n");
                printf("------------------------------------------------------------------------------------------\n");
                printf("%-6d | %-17s | %-15s | %-9d | %-7s | %.2f\n",
                        produto[i].cod_produto,
                        produto[i].nome,
                        produto[i].categoria,
                        produto[i].quant_estoque,
                        produto[i].unid_venda,
                        produto[i].preco);
                printf("------------------------------------------------------------------------------------------\n");
                entr = produto[i];
                prodEnc = 1;
                break;
            }
        }
        
        if(!prodEnc) {
            printf("Produto nao encontrado. Tente novamente!\n");
        }
    } while(!prodEnc);
    
    printf("Informe a quantidade que deseja adicionar em estoque para este produto:\n");
    scanf("%d", &quantComp);

    entr.quant_anterior = entr.quant_estoque;
    entr.quant_estoque = adicionaProduto(quantComp, entr.quant_estoque);
    printf("\nNovo estoque: %d\n", entr.quant_estoque);

    for (int i = 0; i < contador; i++) {
        if (produto[i].cod_produto == entr.cod_produto) {
            produto[i] = entr;
            break;
        }
    }

    for (int i = 0; i < contador; i++) {
        fprintf(ARQUIVO_TEMP_CADASTRO, "%d, %s, %s, %d, %s, %.2f\n",
                produto[i].cod_produto,
                produto[i].nome,
                produto[i].categoria,
                produto[i].quant_estoque,
                produto[i].unid_venda,
                produto[i].preco);
    }

    printf("\nProduto atualizado:\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("Codigo    | Nome                | Categoria          | Qtde     | Unidade     | Preco   \n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("%-6d | %-17s | %-15s | %-9d | %-7s | %.2f\n",
            entr.cod_produto,
            entr.nome,
            entr.categoria,
            entr.quant_estoque,
            entr.unid_venda,
            entr.preco);
    printf("------------------------------------------------------------------------------------------\n");

    fprintf(PRODUTO_ENTRADA, "----------------------------------------------------------------------------------------------------------------------\n");
    fprintf(PRODUTO_ENTRADA, "Cod. Entrada | Codigo    | Nome                | Categoria          | Qtde | Qtde. Anterior | Unidade     | Preco   \n");
    fprintf(PRODUTO_ENTRADA, "----------------------------------------------------------------------------------------------------------------------\n");
    fprintf(PRODUTO_ENTRADA, "%-12d | %-9d | %-19s | %-18s | %-4d | %-14d | %-11s | %.2f\n",
            entr.cod_entrada,
            entr.cod_produto,
            entr.nome,
            entr.categoria,
            entr.quant_estoque,
            entr.quant_anterior,
            entr.unid_venda,
            entr.preco);
    fprintf(PRODUTO_ENTRADA, "----------------------------------------------------------------------------------------------------------------------\n");

    fclose(PRODUTO_ENTRADA);
    fclose(PRODUTO_CADASTRO);
    fclose(ARQUIVO_TEMP_CADASTRO);

    remove("tela_cadastro.txt");
    rename("arquivo_temp_cadastro.txt", "tela_cadastro.txt");
    
    opcRetorno = retornoTela(opcRetorno);
    if (opcRetorno == 0) {
        main();
    }
    else {
        exit(0);
    }
}

void telaSaida() {
    struct Saida{
        int cod_saida, cod_produto, quant_estoque, quantidade_anterior;
        char nome[50], categoria[20], unid_venda[4];
        float preco;
    }saida, produto[100];

    int opcRetorno = 0, contador = 0, quantidadeMaxima = 100, codigoDigitado, produtoEncontrado = 0, quantidadeSaida;
    char linha[200];

    FILE *ARQUIVO_PRODUTO, *ARQUIVO_SAIDA, *ARQUIVO_TEMP;

    system("cls");

    printf("\n================================================================================================\n");
    printf("====================================TELA DE SAIDA DE PRODUTO====================================\n");
    printf("================================================================================================\n");

    ARQUIVO_PRODUTO = fopen("tela_cadastro.txt", "r");
    ARQUIVO_SAIDA = fopen("tela_saida.txt", "a+");
    ARQUIVO_TEMP = fopen("arquivo_temp_saida.txt", "a+");

    if(ARQUIVO_PRODUTO == NULL) {
        printf("\nErro(Saida)!\n");
        exit(1);
    }

    if(ARQUIVO_SAIDA == NULL) {
        printf("\nErro(Cadastro)!\n");
        exit(1);
    }

    if(ARQUIVO_TEMP == NULL) {
        printf("\nErro(Arquivo temporario)!");
        exit(1);
    }

    while(fgets(linha, sizeof(linha), ARQUIVO_PRODUTO) && contador < quantidadeMaxima) {
        if(sscanf(linha, "%d, %49[^,], %19[^,], %d, %3[^,], %f", &saida.cod_produto, saida.nome, saida.categoria, &saida.quant_estoque, saida.unid_venda, &saida.preco) == 6) {
            produto[contador] = saida;
            contador++;
        }
        else {
            printf("Erro ao ler a linha: %s", linha);
        }
    }

    do {
        fflush(stdin);
        printf("Digite o codigo do produto que deseja realizar a saida:\n");
        scanf("%d", &codigoDigitado);

        for(int i = 0; i < contador; i++) {
            if(produto[i].cod_produto == codigoDigitado) {
                printf("\nProduto encontrado:\n");
                printf("------------------------------------------------------------------------------------------\n");
                printf("Codigo    | Nome                | Categoria          | Qtde     | Unidade     | Preco   \n");
                printf("------------------------------------------------------------------------------------------\n");
                printf("%-6d | %-17s | %-15s | %-9d | %-7s | %.2f\n",
                        produto[i].cod_produto,
                        produto[i].nome,
                        produto[i].categoria,
                        produto[i].quant_estoque,
                        produto[i].unid_venda,
                        produto[i].preco);
                printf("------------------------------------------------------------------------------------------\n");
                saida = produto[i];
                produtoEncontrado = 1;
                break;
            }
        }
        
        if(!produtoEncontrado) {
            printf("Produto nao encontrado. Tente novamente!\n");
        }
    } while(!produtoEncontrado);

    do {
        printf("Informe a quantidade que deseja retirar do estoque para este produto:\n");
        scanf("%d", &quantidadeSaida);

        if(!validaQuantidadeSaida(quantidadeSaida)) {
            printf("Quantidade nao pode ser negativa!\n");
        }

        if(!verificaTotSaida(quantidadeSaida, saida.quant_estoque)) {
            printf("Quantidade digitada nao pode ser maior que quantidade em estoque. Tente novamente!\n");
        }
    } while(!verificaTotSaida(quantidadeSaida, saida.quant_estoque) || !validaQuantidadeSaida(quantidadeSaida));

    saida.quantidade_anterior = saida.quant_estoque;
    saida.quant_estoque = removeProduto(quantidadeSaida, saida.quant_estoque);
    printf("\nNovo estoque: %d\n", saida.quant_estoque);

    for (int i = 0; i < contador; i++) {
        if (produto[i].cod_produto == saida.cod_produto) {
            produto[i] = saida;
            break;
        }
    }

    for (int i = 0; i < contador; i++) {
        fprintf(ARQUIVO_TEMP, "%d, %s, %s, %d, %s, %.2f\n",
                produto[i].cod_produto,
                produto[i].nome,
                produto[i].categoria,
                produto[i].quant_estoque,
                produto[i].unid_venda,
                produto[i].preco);
    }

    printf("\nProduto atualizado:\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("Codigo    | Nome                | Categoria          | Qtde     | Unidade     | Preco   \n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("%-6d | %-17s | %-15s | %-9d | %-7s | %.2f\n",
            saida.cod_produto,
            saida.nome,
            saida.categoria,
            saida.quant_estoque,
            saida.unid_venda,
            saida.preco);
    printf("------------------------------------------------------------------------------------------\n");

    fprintf(ARQUIVO_SAIDA, "----------------------------------------------------------------------------------------------------------------------\n");
    fprintf(ARQUIVO_SAIDA, "Cod. Saida   | Codigo    | Nome                | Categoria          | Qtde | Qtde. Anterior | Unidade     | Preco   \n");
    fprintf(ARQUIVO_SAIDA, "----------------------------------------------------------------------------------------------------------------------\n");
    fprintf(ARQUIVO_SAIDA, "%-12d | %-9d | %-19s | %-18s | %-4d | %-14d | %-11s | %.2f\n",
            saida.cod_saida,
            saida.cod_produto,
            saida.nome,
            saida.categoria,
            saida.quant_estoque,
            saida.quantidade_anterior,
            saida.unid_venda,
            saida.preco);
    fprintf(ARQUIVO_SAIDA, "----------------------------------------------------------------------------------------------------------------------\n");

    fclose(ARQUIVO_PRODUTO);
    fclose(ARQUIVO_SAIDA);
    fclose(ARQUIVO_TEMP);

    remove("tela_cadastro.txt");
    rename("arquivo_temp_saida.txt", "tela_cadastro.txt");

    opcRetorno = retornoTela(opcRetorno);
    if (opcRetorno == 0) {
        main();
    }
    else {
        exit(0);
    }
}

void telaVenda() {
    struct Produto {
        int codigo_venda, codigo_produto, codigo_digitado, quantidade_estoque, quantidade_venda, tipo_entrega, nota_entrega;
        char nome[50], categoria[20], un[4];
        float valor, valor_final_estoque, valor_final_venda;
    }venda, produto[100];

    //GERA OS NUMEROS ALEATORIOS PARA CADA PRODUTO
    srand(time(NULL));
    venda.codigo_venda = rand() % 100; //GERA UM NÚMERO ENTRE 0 E 99

    int opcRetorno = 0, produtoEncontrado = 0, contador = 0, loop = 0, quantidadeMaxima = 100;
    char linha[200];

    FILE *PRODUTO_CADASTRO, *PRODUTO_VENDA, *ENTREGA_REALIZADAS, *ARQ_TEMP;

    system("cls");

    printf("\n================================================================================================\n");
    printf("=========================================TELA DE VENDAS=========================================\n");
    printf("================================================================================================\n");

    PRODUTO_CADASTRO = fopen("tela_cadastro.txt", "r");
    PRODUTO_VENDA = fopen("tela_venda.txt", "a+");
    ENTREGA_REALIZADAS = fopen("entregas_re.txt", "a+");
    ARQ_TEMP = fopen("arquivo_temp_venda.txt", "a+");

    if(PRODUTO_CADASTRO == NULL) {
        printf("\nErro(Cadastro)!\n");
        exit(1);
    }

    if(ARQ_TEMP == NULL) {
        printf("\nErro(Arquivo temporario)!\n");
        exit(1);
    }

    if(PRODUTO_VENDA == NULL) {
        printf("\nErro(Vendas)\n");
    }

    while(fgets(linha, sizeof(linha), PRODUTO_CADASTRO) && contador < quantidadeMaxima) {
        if(sscanf(linha, "%d, %49[^,], %19[^,], %d, %3[^,], %f", &venda.codigo_produto, venda.nome, venda.categoria, &venda.quantidade_estoque, venda.un, &venda.valor) == 6) {
            produto[contador] = venda;
            contador++;   
        }
        else {
            printf("Erro ao ler a linha: %s", linha);
        }
    }

    printf("Digite o codigo do produto desejado:");
    scanf("%d", &venda.codigo_digitado);

    for(int i = 0; i < contador; i++) {
        if(produto[i].codigo_produto == venda.codigo_digitado) {
            printf("\nProduto encontrado:\n");
            printf("------------------------------------------------------------------------------------------\n");
            printf("Codigo    | Nome                | Categoria          | Qtde     | Unidade     | Preco   \n");
            printf("------------------------------------------------------------------------------------------\n");
            printf("%-6d | %-17s | %-15s | %-9d | %-7s | %.2f\n",
                    produto[i].codigo_produto,
                    produto[i].nome,
                    produto[i].categoria,
                    produto[i].quantidade_estoque,
                    produto[i].un,
                    produto[i].valor);
            printf("------------------------------------------------------------------------------------------\n");
            venda = produto[i];
            produtoEncontrado = 1;
            break;
        }
    }

    if (!produtoEncontrado) {
        printf("\nProduto com codigo %d nao encontrado.\n", venda.codigo_digitado);
    }
    loop = 0;
    do {
        fflush(stdin);
        printf("\nQuantas unidades de %s deseja comprar ?\n", venda.nome);
        
        if (scanf("%d", &venda.quantidade_venda) != 1 || venda.quantidade_venda > venda.quantidade_estoque) {
            if  (venda.quantidade_venda > venda.quantidade_estoque) {
                printf("A quantidade informada e superior a quantidade em estoque. Tente novamente!");
            }
            else {
                printf("Erro: Voce digitou um valor invalido!\n");
            }
            
            loop = 1;
        }
        else {
            loop = 0;
        }

        if(venda.quantidade_venda == 0) {
            printf("Quantidade de venda deve ser maior que zero!");
            loop = 1;
        }

    } while(loop !=0);

    venda.valor_final_venda = venda.valor * venda.quantidade_venda;
    venda.quantidade_estoque -= venda.quantidade_venda;

    for (int i = 0; i < contador; i++) {
        if (produto[i].codigo_produto == venda.codigo_produto) {
            produto[i] = venda;
            break;
        }
    }

    for (int i = 0; i < contador; i++) {
        fprintf(ARQ_TEMP, "%d, %s, %s, %d, %s, %.2f\n",
                produto[i].codigo_produto,
                produto[i].nome,
                produto[i].categoria,
                produto[i].quantidade_estoque,
                produto[i].un,
                produto[i].valor);
    }

    do {
        fflush(stdin);
        printf("\n Digite a opcao de de entrega desejada: (1 ou 2)\n");
        printf("1 - Com entrega\n");
        printf("2 - Sem Entrega\n");
        scanf("%d", &venda.tipo_entrega);
    } while(venda.tipo_entrega != 1 && venda.tipo_entrega != 2);


    if(venda.tipo_entrega == 1) {
        fprintf(PRODUTO_VENDA, "%d, %d, %s, %s, %d, %s, %.2f, %.2f, %d\n", venda.codigo_venda, venda.codigo_produto, venda.nome, venda.categoria, venda.quantidade_venda, venda.un, venda.valor, venda.valor_final_venda, venda.tipo_entrega);
    }
    
    if(venda.tipo_entrega == 2) {
        srand(time(NULL));
        venda.nota_entrega = rand() % 900000 + 100000;
        fprintf(ENTREGA_REALIZADAS, "--------------------------------------------------------------------------------------------------------------------\n");
        fprintf(ENTREGA_REALIZADAS, "Codigo de Venda   | Nome                | Categoria          | Qtde     | Unidade     | Preco   | Codigo de entrega \n");
        fprintf(ENTREGA_REALIZADAS, "--------------------------------------------------------------------------------------------------------------------\n");
        fprintf(ENTREGA_REALIZADAS, "%-9d | %-19s | %-18s | %-8d | %-11s | %.2f | %d\n",
                venda.codigo_venda,
                venda.nome,
                venda.categoria,
                venda.quantidade_venda,
                venda.un,
                venda.valor_final_venda,
                venda.nota_entrega);
        fprintf(ENTREGA_REALIZADAS, "--------------------------------------------------------------------------------------------------------------------\n\n");
    }
        
    fclose(PRODUTO_CADASTRO);
    fclose(PRODUTO_VENDA);
    fclose(ENTREGA_REALIZADAS);
    fclose(ARQ_TEMP);

    remove("tela_cadastro.txt");
    rename("arquivo_temp_venda.txt", "tela_cadastro.txt");

    opcRetorno = retornoTela(opcRetorno);
    if (opcRetorno == 0) {
        main();
    }
    else {
        exit(0);
    }
}

void telaEntrega() {
    struct Produto {
        int codigo_venda, codigo_produto, codigo_digitado, quantidade_estoque, quantidade_venda, tipo_entrega;
        char nome[50], categoria[20], un[4];
        float valor, valor_final_estoque, valor_final_venda;
    }venda;

    int opcRetorno = 0, delivery_id, found = 0, line = 0, line_c = 0, menu, nota_entrega;
    char linha[256], linha_mov[256], subMenu;

    FILE *arq_ent, *arq_ent_re, *arq_temp;

    system("cls");

    printf("\n================================================================================================\n");
    printf("================================TELA DE ENTREGAS DE MERCADORIA==================================\n");
    printf("================================================================================================\n");

    do {
        printf("1 - Ver entregas pendentes\n2 - Realizar entrega\n3 - Ver entregas realizadas\n4 - Sair\n");
        printf("Escolha o que deseja realizar: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                arq_ent = fopen("tela_venda.txt", "r");
                if(arq_ent == NULL){
                    printf("Erro ao ler o arquivo");
                }
                system("cls");
                while (fgets(linha, sizeof(linha), arq_ent) != NULL) {
                    printf("%s", linha);
                }
                break;
            case 2:
                printf("Digite o codigo da entrega a realizar: ");
                scanf("%d", &delivery_id);

                arq_ent = fopen("tela_venda.txt", "r");
                if (arq_ent == NULL) {
                    printf("Erro ao ler o arquivo");
                    return;
                }
                while (fgets(linha, sizeof(linha), arq_ent) != NULL) {
                    line++;
                    if (sscanf(linha, "%d, %d, %49[^,], %19[^,], %d, %3[^,], %f, %f, %d\n", &venda.codigo_venda, &venda.codigo_produto, venda.nome, venda.categoria, &venda.quantidade_venda, venda.un, &venda.valor, &venda.valor_final_venda, &venda.tipo_entrega) == 9 && venda.codigo_venda == delivery_id)
                    {
                        found = 1;
                        strcpy(linha_mov, linha);
                        srand(time(NULL));
                        nota_entrega = rand() % 900000 + 100000;
                        break;
                    }
                }
                if(!found) {
                    system("cls");
                    printf("Entrega nao encontrada\n");
                    fclose(arq_ent);
                    break;
                }
                rewind(arq_ent);
                arq_temp = fopen("temp.txt", "w");
                if(arq_temp == NULL) {
                    printf("Error ao criar arquivo temporario\n");
                    fclose(arq_temp);
                    return;
                }
                while (fgets(linha, sizeof(linha), arq_ent) != NULL) {
                    line_c++;
                    if (line_c == line) {
                        continue;
                    }
                    fputs(linha, arq_temp);
                }
                fclose(arq_temp);
                fclose(arq_ent);
                remove("tela_venda.txt");
                rename("temp.txt", "tela_venda.txt");

                arq_ent_re = fopen("entregas_re.txt", "a+");
                if(arq_ent_re == NULL) {
                    printf("Error ao abrir arquivo de entregas realizadas");
                    fclose(arq_ent_re);
                }
                fprintf(arq_ent_re, "--------------------------------------------------------------------------------------------------------------------\n");
                fprintf(arq_ent_re, "Codigo de Venda   | Nome                | Categoria          | Qtde     | Unidade     | Preco   | Codigo de entrega \n");
                fprintf(arq_ent_re, "--------------------------------------------------------------------------------------------------------------------\n");
                fprintf(arq_ent_re, "%-9d | %-19s | %-18s | %-8d | %-11s | %.2f | %d\n",
                    venda.codigo_venda,
                    venda.nome,
                    venda.categoria,
                    venda.quantidade_venda,
                    venda.un,
                    venda.valor_final_venda,
                    nota_entrega);
                fprintf(arq_ent_re, "--------------------------------------------------------------------------------------------------------------------\n\n");
                fclose(arq_ent_re);
                line = 0;
                line_c = 0;

                printf("Entrega realizada com sucesso!\n");

                break;
            case 3:
                arq_ent_re = fopen("entregas_re.txt", "r");
                if (arq_ent_re == NULL) {
                    printf("Erro ao Abrir o Arquivo\n");
                    return;
                }
                system("cls");
                while (fgets(linha, sizeof(linha), arq_ent_re) != NULL) {
                    printf("%s", linha);
                }
                fclose(arq_ent_re);
                break;
            case 4:
                system("cls");
                printf("Voce saiu da tela de entrega\n");
                main();
            default:
                system("cls");
                printf("Escolha uma opcao valida\n");
                break;
        }
        if(menu != 4){
            do{
                printf("\nDeseja voltar a tela de entregas? (S/N): ");
                scanf(" %c", &subMenu);
                if(subMenu == 'S' || subMenu == 's') {
                    break;
                } else if(subMenu == 'N' || subMenu == 'n') {
                    main();
                } else {
                    system("cls");
                    printf("Opcao invalida, digite novamente!\n");
                }
            }while(subMenu != 'S' && subMenu != 's' && subMenu != 'N' && subMenu != 'n');  
        }
    } while(menu != 4);
    
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

    struct Pesquisa{
        int cod_produto, quant_estoque;
        char nome[50], categoria[20], unid_venda[4];
        float preco;
    }pesq, produto[100];

    int contador = 0, quantidadeMaxima = 100;
    char linha[200];

    FILE *PESQUICA;

    system("cls");

    printf("\n================================================================================================\n");
    printf("=================================TELA DE PESQUISA DE PRODUTO====================================\n");
    printf("================================================================================================\n");

    //INSIRA O CODIGO APARTIR DAQUI DECLARANDO A VARIAVEL JUNTO DA VARIAVEL ACIMA

    PESQUICA = fopen("tela_cadastro.txt", "r");

    if(PESQUICA == NULL){
        printf("\nERRO!!\n");
        exit(1);
    }

    while(fgets(linha, sizeof(linha), PESQUICA) && contador < quantidadeMaxima) {
        if(sscanf(linha, "%d, %49[^,], %19[^,], %d, %3[^,], %f", &pesq.cod_produto, pesq.nome, pesq.categoria, &pesq.quant_estoque, pesq.unid_venda, &pesq.preco) == 6) {
            produto[contador] = pesq;
            contador++;
        }
        else {
            printf("Erro ao ler a linha: %s", linha);
        }
    }

    printf("\nProduto encontrado:\n\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("Codigo    | Nome                | Categoria          | Qtde     | Unidade     | Preco   \n");

    for(int i = 0; i < contador; i++) {
            
                printf("------------------------------------------------------------------------------------------\n");
                printf("%-9d | %-19s | %-18s | %-8d | %-11s | %.2f\n",
                        produto[i].cod_produto,
                        produto[i].nome,
                        produto[i].categoria,
                        produto[i].quant_estoque,
                        produto[i].unid_venda,
                        produto[i].preco);
                printf("------------------------------------------------------------------------------------------\n");

            }

    fclose(PESQUICA);    

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

void configuracao() {
    char escolha;
        do {
            printf("\nApagar banco dados? (S/N) ");
            scanf(" %c", &escolha);

            if(escolha == 'S' || escolha == 's') {
                remove("tela_cadastro.txt");
                remove("tela_saida.txt");
                remove("tela_cadastro.txt");
                remove("tela_entrada.txt");
                remove("tela_venda.txt");
                remove("entregas_re.txt");
                remove("arquivo_temp_saida.txt");
                remove("arquivo_temp_venda.txt");
                remove("temp.txt");
            } else if(escolha == 'N' || escolha == 'n') {
                main();
            } else {
                printf("Opcao invalida, digite novamente!\n");
            }  
    } while(escolha != 'S' && escolha != 's' && escolha != 'N' && escolha != 'n');
}