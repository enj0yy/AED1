#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _pilha
{
    int * valores;
    int topo;
    int base;
    int n_valores;
} Pilha;


void Reset(Pilha * pilha)
{
    pilha->valores = NULL;
    pilha->topo = 0;
    pilha->base = 0;
    pilha->n_valores = 0;
}

int Empty(Pilha * pilha)
{
    return pilha->topo == 0;
}

int Push(Pilha * pilha, int valor)
{
    pilha->n_valores++;
    pilha->valores = realloc(pilha->valores, sizeof(int)*pilha->n_valores);

    if (pilha->valores == NULL)
    {
        printf("Erro na alocaçao!");
        exit(1);
    }

    pilha->valores[pilha->topo] = valor;
    pilha->topo++;

    return 1;
}

void Pop(Pilha * pilha, int * valor_pop)
{
    if (!Empty(pilha))
    {
        pilha->topo--; 
        *valor_pop = pilha->valores[pilha->topo];
        pilha->n_valores--;
        pilha->valores = realloc(pilha->valores,sizeof(int)*pilha->n_valores);   
    }
}

void List(Pilha * pilha)
{
    int valor_pop;
    Pilha * pilha_copia;
    pilha_copia = (Pilha*)malloc(sizeof(Pilha));

    if (pilha_copia == NULL)
    {
        printf("Erro na alocaçao!");
        exit(1);
    }

    Reset(pilha_copia);

    while(!Empty(pilha))
    {
        Pop(pilha,&valor_pop);
        Push(pilha_copia,valor_pop);
        printf("Valor: %d \n",valor_pop);
    }

    while(!Empty(pilha_copia))
    {
        Pop(pilha_copia,&valor_pop);
        Push(pilha,valor_pop);
    }
    free(pilha_copia);
}

void Clear(Pilha * pilha)
{
    int valor_pop;
    while(!Empty(pilha))
    {
        Pop(pilha,&valor_pop);
    }
}

int main()
{
    Pilha * pilha;
    pilha = (Pilha*)malloc(sizeof(Pilha));

    if (pilha == NULL)
    {
        printf("Erro na alocaçao!");
        exit(1);
    }
    Reset(pilha);

    Push(pilha,1);
    Push(pilha,2);
    Push(pilha,3);

    printf("Pilha:\n");
    List(pilha);

    int valor_pop;
    printf("Pop:\n");
    Pop(pilha,&valor_pop);
    List(pilha);

    printf("Limpando a pilha:\n");
    Clear(pilha);
    List(pilha);

    free(pilha);
    return 0;
}