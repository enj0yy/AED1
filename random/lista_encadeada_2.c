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
    Nodo * pfirst;
} Lista;


int Empty(Lista * lista);
void Clear(Lista * lista);
Lista * Reset(Lista * lista);
void PushEnd(Lista * lista, Produto produto);
void Pop(Lista * lista, int index);
void List(Lista * lista);
Produto NewProduto(int codigo, char * nome, float preco);


int main()
{
    Lista * lista = NULL;
    lista = Reset(lista);

    printf("\nLista:\n");
    PushEnd(lista,NewProduto(1,"Sabonete",4.30));
    PushEnd(lista,NewProduto(2,"Arroz",5));
    PushEnd(lista,NewProduto(3,"Cafe",6));
    PushEnd(lista,NewProduto(4,"Pao",3));
    List(lista);

    printf("\nLista depois de deletar o segundo item[index 1] item:\n");
    Pop(lista,1);
    List(lista);

    printf("\nLista depois de inserir um novo item:\n");
    PushEnd(lista,NewProduto(6,"Produto Novo!",4.30));
    List(lista);

    Clear(lista);
    free(lista);
    return 0;
}

int Empty(Lista * lista)
{
    return lista->pfirst == NULL;
}

void Clear(Lista * lista)
{
    while(!Empty(lista))
    {
        Pop(lista,0);
    }
}

Lista * Reset(Lista * lista)
{
    if(lista)
        Clear(lista);

    lista = (Lista*)malloc(sizeof(Lista));
    lista->pfirst = NULL;
    return lista;
}

void PushEnd(Lista * lista, Produto produto)
{
    Nodo * nodo = (Nodo*)malloc(sizeof(Nodo));
    Nodo * p;

    nodo->produto = produto;
    nodo->pNext = NULL;

    if (lista->pfirst == NULL)                  
    {
        lista->pfirst = nodo;
    }
    else
    {
        for (p = lista->pfirst; p->pNext != NULL; p = p->pNext);
        p->pNext = nodo;
    }

    nodo = NULL;
    p = NULL;
    free(nodo);
    free(p);
}

void Pop(Lista * lista, int index)
{
    Nodo * p = NULL;
    Nodo * p2 = NULL;
    int i = 1;

    if(Empty(lista))
        return;
    
    if (index == 0)
    {
        p = lista->pfirst;
        lista->pfirst = lista->pfirst->pNext;
        free(p);
    }
    else
    {
        p2 = lista->pfirst;
        for (p = lista->pfirst->pNext; p != NULL; p = p->pNext)
        {
            if (index == i)
            {
                p2->pNext = p->pNext;
                free(p);
                break;
            }
            p2 = p;
            i++;
        }
    }

    p = NULL;
    free(p);   
    p2 = NULL;
    free(p2);  
}

void List(Lista * lista)
{
    Nodo * p;
    int index = 0;
    for (p = lista->pfirst; p != NULL; p = p->pNext)
    {
        printf("[%d] %d %s %.2f\n",index,p->produto.cod,p->produto.nome,p->produto.preco);
        index++;
    }

    p = NULL;
    free(p);
}

Produto NewProduto(int codigo, char * nome, float preco)
{
    Produto produto;
    produto.cod = codigo;
    strcpy(produto.nome,nome);
    produto.preco = preco;
    return produto;
}
