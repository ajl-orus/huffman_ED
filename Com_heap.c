#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<time.h>
#define MAX 1000
typedef struct element
{
    int prioridade;
} element;

typedef struct fila
{
    int quant;
    element *dados[MAX];
} Fila;

Fila *create()
{

    Fila *new = (Fila *)malloc(sizeof(Fila));
    new->quant = 0;
    for (int i = 0; i < MAX; i++)
    {
        new->dados[i] = NULL;
    }
    return new;
}
void swap(Fila *fila,int i1, int i2)
{
    element *aux = fila->dados[i1];
    fila->dados[i1] = fila->dados[i2];
    fila->dados[i2] = aux;
}
int indice_pai(Fila *heap, int i)
{
    return (i-1) / 2;
}
int get_left_index(Fila *heap, int i)
{
    return 2 * i + 1;
}
int get_right_index(Fila *heap, int i)
{
    return 2 * i + 2;
}

int add(Fila *fila,int prioridade)
{
    int contador = 0;
    if (fila->quant == MAX - 1)
    {
        return contador;
    }
    else
    {
        element *new = (element *)malloc(sizeof(element));
   
        new->prioridade = prioridade;
        fila->dados[fila->quant++] = new;
        int ind_pai = indice_pai(fila, fila->quant - 1);
        int index = fila->quant - 1;
        while (index >= 1 && fila->dados[index]->prioridade > fila->dados[ind_pai]->prioridade)
        {

            swap(fila, ind_pai, index);
            index = ind_pai;
            ind_pai = indice_pai(fila,index);
contador++;
        }
    }
    return contador;
}





int main()
{
    
    Fila *fila = create();

    FILE *fp = fopen("resultados", "w");
    srand(time(NULL));
    for(int i = 0; i < 1000; i++){
        int aux = add(fila, rand());
fprintf(fp, "%d\n", aux);
    }
    
  fclose(fp);
    



}