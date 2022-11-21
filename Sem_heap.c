#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX 10000 // Heap.

//............Fila de Prioridade sem Heap............//

typedef struct no{
    int item;
    int prioridade;
    struct no *next;
}NO;

typedef struct Fila{
    struct no *head;
}FILA;

FILA* criar_fila_vazia()
{
    FILA *novo_no = (FILA*) malloc(sizeof(FILA));
    novo_no->head= NULL;
    return novo_no;
}

void enfileirar(FILA *pq, int item, int prioridade,FILE* arq){
    NO *novo_no = (NO*) malloc(sizeof(NO));
    novo_no->item = item;                                  
    novo_no->prioridade = prioridade;                     
    int contador = 1;
    if((pq->head==NULL) || novo_no->prioridade > pq->head->prioridade){
        novo_no->next = pq->head;
        pq->head = novo_no;
    }
    else{
        NO *atual = pq->head;
        contador = 2;
        while((atual->next != NULL) && atual->next->prioridade > prioridade){
            atual = atual->next;
            contador++;
        }
        novo_no->next = atual->next;
        atual->next = novo_no;
    }
    fprintf(arq,"%d\n",contador);
}

NO* desenfileirar(FILA *pq){
    if(pq->head==NULL){
        return NULL;
    }
    else{
        NO *no = pq->head;
        pq->head = pq->head->next;
        no->next = NULL;
        return no;
    }
}

int busca(FILA* no, int item){
    NO* aux = no->head;
    while(aux !=NULL){
        if(aux->item == item){
            printf("O item %d está aqui\n\n", item);
            return;
        }
        aux = aux->next;
    }
}

void print(FILA *no){
    NO *atual = no->head;
    printf("\n");
    while(atual->next != NULL){
        printf("%d ", atual->item);
        atual = atual->next;
    }
    printf("%d\n", atual->item);
}

//.....................Interface.....................//


int Inspecao(FILA *f,FILA_PRIO* f_heap,FILE* arq, FILE*arquivo2,int tamanho){
    printf("\nDigite o procedimento:\n1-Enfileirar\n2-Desenfileirar\n3-Buscar\n4-printar\n5-Retornar\n");
    int procedimento;
    scanf("%d", &procedimento);
    if(procedimento==1){
        int item,prioridade;
        scanf("%d, %d", &item, &prioridade);
        enfileirar(f,item,prioridade,arq);
        enfileirar_heap(f_heap,item,prioridade,arquivo2);
        Inspecao(f,f_heap,arq,arquivo2,tamanho);
    }
    else if(procedimento==2){
        desenfileirar(f);
        desenfileirar_heap(f_heap);
        Inspecao(f,f_heap,arq,arquivo2,tamanho);
    }
    else if(procedimento==3){
        int buscado;
        printf("Digite o item buscado:\n");
        scanf("%d", &buscado);
        busca(f,buscado);
        busca_heap(f_heap,buscado);
        Inspecao(f,f_heap,arq,arquivo2,tamanho);
    }
    else if(procedimento==4){
        print(f);
        print_heap(f_heap);
        Inspecao(f,f_heap,arq,arquivo2,tamanho);
    }
    else if(procedimento==5){
        return;
    }
    else{
        printf("\nERRO, tente de Novo!\n\n");
        Inspecao(f,f_heap,arq,arquivo2,tamanho);
    }
}

int Analise(FILA* f,FILA_PRIO* f_heap,FILE* arquivo,FILE* arquivo2,int controle){
    int i;
    int tamanho = 10000;
    if(controle==0){
        for(i=tamanho;i>0;i--){
            enfileirar(f,i,i,arquivo);
        }
        for(i=1;i<=tamanho;i++){
            enfileirar_heap(f_heap,i,i,arquivo2);
        }
    }
    printf("\nDigite:\n1-Inspecionar e Alterar fila\n2-Plotagem dos dados\n3-Fechar Programa\n");
    int comando;
    scanf("%d", &comando);
    if(comando==1){
        Inspecao(f,f_heap,arquivo,arquivo2,tamanho);
        Analise(f,f_heap,arquivo,arquivo2,1);
    }
    else if(comando==2){
        printf("Iniciando processo de Plotagem\n\n");
        Analise(f,f_heap,arquivo,arquivo2,1);
    }
    else if(comando==3){
        return;
    }
    else{
        printf("\nErro, tente de novo!\n");
        Analise(f,f_heap,arquivo,arquivo2,1);
    }
    return 0;
}

int main(){
    FILA* f = criar_fila_vazia();
    FILA_PRIO* f_heap = criar_Fila_heap();
    FILE* arquivo = fopen("1-Plotagem_sem_heap.txt", "w");
    FILE* arquivo2 = fopen("2-Plotagem_com_heap.txt","w");
    Analise(f,f_heap,arquivo,arquivo2,0);
    fclose(arquivo);
    fclose(arquivo2);
    return 0;
}
