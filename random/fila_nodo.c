#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int cod;
    char nome[40];
    float preco;
} Produto;

typedef struct _nodo 
{
    Produto produto;
    struct _nodo * pNext;
} Nodo;

typedef struct 
{
    Nodo * pFirst;
    Nodo * pLast;
} Fila;


int Empty(Fila * fila);
void Clear(Fila * fila);
Fila * Reset(Fila * fila);
Produto NewProduto(int codigo, char * nome, float preco);
void Push(Fila * fila, Produto produto);
void PushHeap(Fila * fila, Produto produto);
int Pop(Fila * fila, Nodo * nodo_pop);
void List(Fila * fila);


int main()
{
    printf("----------------------------\n");
    printf("Fila:\n");
    Fila * fila = NULL;
    fila = Reset(fila);

    Push(fila,NewProduto(4,"Suco",2));
    Push(fila,NewProduto(1,"Leite",5.32));
    Push(fila,NewProduto(2,"Arroz",4));

    List(fila);
    Clear(fila);
    free(fila);

    printf("----------------------------\n");
    printf("Fila de prioridade (Codigo):\n");
    Fila * fila_prioridade = NULL;
    fila_prioridade = Reset(fila_prioridade);

    PushHeap(fila_prioridade,NewProduto(4,"Suco",2));
    PushHeap(fila_prioridade,NewProduto(1,"Leite",5.32));
    PushHeap(fila_prioridade,NewProduto(2,"Arroz",4));

    List(fila_prioridade);
    Clear(fila_prioridade);
    free(fila_prioridade);
}

int Empty(Fila * fila)
{
    return fila->pFirst == NULL;
}

void Clear(Fila * fila)
{
    Nodo nodo_pop;
    while (!Empty(fila))
    {
        Pop(fila, &nodo_pop);
    }
}

Fila * Reset(Fila * fila)
{
    if(fila)
        Clear(fila);

    fila = (Fila*)malloc(sizeof(Fila));
    fila->pFirst = NULL;
    fila->pLast = NULL;

    return fila;
}

Produto NewProduto(int codigo, char * nome, float preco)
{
    Produto produto;
    produto.cod = codigo;
    strcpy(produto.nome,nome);
    produto.preco = preco;
    return produto;
}

void Push(Fila * fila, Produto produto)
{
    Nodo * nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->produto = produto;
    nodo->pNext = NULL;

    if(Empty(fila))
    {
        fila->pFirst = nodo;
        fila->pLast = nodo;
    }
    else
    {
        fila->pLast->pNext = nodo;
        fila->pLast = nodo;
    }
}

void PushHeap(Fila * fila, Produto produto)
{
    Nodo * p = fila->pFirst;
    Nodo * p2 = fila->pFirst;
    Nodo * nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->produto = produto;
    nodo->pNext = NULL;

    if(Empty(fila))         //inserir em uma fila vazia
    {
        fila->pFirst = nodo;
        fila->pLast = nodo;
    }
    else
    {
        p2 = fila->pFirst;
        for(p = fila->pFirst; p!=NULL; p = p->pNext)
        {
            if( (fila->pFirst == p) && (produto.cod <= p->produto.cod) ) //inserir no começo
            {
                nodo->pNext = p;
                fila->pFirst = nodo;
                break;
            }
            if (produto.cod <= p->produto.cod)                          //inserir no meio
            {
                p2->pNext = nodo;
                nodo->pNext = p;
                break;
            }
            if(p->pNext == NULL && produto.cod >= p->produto.cod)       //inserir no final
            {
                p->pNext = nodo;
                fila->pLast = nodo;
                break;
            }
            p2 = p;
        }
    }
    p = NULL;
    p2 = NULL;
    free(p);
    free(p2);
}

int Pop(Fila * fila, Nodo * nodo_pop)
{
    Nodo * p;
    int pop_feito = 0;

    if(!Empty(fila))
    {
        *nodo_pop = *fila->pFirst;
        p = fila->pFirst;  

        fila->pFirst = fila->pFirst->pNext;
        if (fila->pFirst == NULL)
            fila->pLast = NULL;

        free(p);
        pop_feito = 1;
    }

    p = NULL;
    free(p);
    return pop_feito;
}

void List(Fila * fila)
{
    Fila * fila_temp = NULL;
    fila_temp = Reset(fila_temp);

    Nodo nodo_pop;

    while (!Empty(fila))
    {
        Pop(fila, &nodo_pop);
        Push(fila_temp,nodo_pop.produto);
        printf("%d %s %.2f\n",nodo_pop.produto.cod,nodo_pop.produto.nome,nodo_pop.produto.preco);
    }

    while (!Empty(fila_temp))
    {
        Pop(fila_temp, &nodo_pop);
        Push(fila,nodo_pop.produto);
    }

    Clear(fila_temp);
    free(fila_temp);
}