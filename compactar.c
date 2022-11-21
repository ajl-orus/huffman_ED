#include "compactar.h"

//Realiza todo o procedimento para compactar.
void compactar()
{
    char nome_do_arquivo[100], caminho[ALTURA_MAX];
    int inteiro, auxiliar;
    unsigned short lixo, tamanho=0; //referência para uso binário.

    printf("\nDigite o nome do arquivo a ser compactado:\n");
    scanf("%s", nome_do_arquivo);

    FILE *arquivo = fopen(nome_do_arquivo, "rb");

    if(arquivo == NULL){
        printf("\nErro no arquivo.\nArquivo Vazio ou inexistente\n\n");
        return;
    }

    printf("\nIniciando processo de compactação...\n\n");

    HT *ht = criar_hash_table();
    adicionar_frequencia(arquivo, ht); //tabela preenchida com frequencia do arquivo.
    rewind(arquivo);
    
    FILA *fila = criar_fila();
    fila = fila_prioridade(ht, fila); //Fila com a ordenação das frequencias.

    criar_arvore_huffman(fila);
    NO *arvore = fila->cabeca; //determinação da raiz da árvore.


    criar_caminho(arvore, ht, caminho, 0);
    printf("\nProcesso em andamento...\n\n"); //codificação do arquivo construida.

    //Inicio do encabeçamento do arquivo comprimido.
    lixo = calcula_tamanho_lixo(ht);
    inteiro = lixo;
    calcula_tamanho_arvore(arvore, &tamanho);

    inteiro = inteiro << 13; //deslocamento de 13 por conta do tamanho armazenado de 2 bytes.
    inteiro = setar_bits(inteiro, &tamanho); 

    *nome_do_arquivo = *strtok(nome_do_arquivo, ".");  //Manipulação de leitura e concatenação do novo arquivo.
    *nome_do_arquivo = *strcat(nome_do_arquivo, ".huff");
    FILE *saida = fopen(nome_do_arquivo, "wb"); //criação e abertura do arquivo de saida em binário.

    auxiliar = inteiro>>8; //colocação do caractere inteiro deslocando em um byte.
    fputc(auxiliar, saida);//No final do arquivo.
    fputc(inteiro, saida);
    imprimir_pre_ordem(saida, arvore);//impressão da árvore.
    fseek(saida, (2 + tamanho), SEEK_SET); //deslocamento sem mudança dentro do arquivo.
    imprimir_bits(arquivo, saida, ht); // Printa todos os bits dentro do arquivo.
    printf("\nProcesso Finalizado!\n\n");
}