#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cel
{
    int valor;
    struct cel * prox;
} Celula;

Celula * cabeca;

void PushEnd(int num)
{
    Celula * p;

    Celula * novo;
    novo = malloc(sizeof(Celula));
    novo->valor = num;
    novo->prox = NULL;

    for(p = cabeca; p->prox != NULL; p = p->prox);
    p->prox = novo;
}

void PushInOrder(int num)
{
    Celula * p = cabeca;
    Celula * p_menos_um = cabeca; 

    Celula * novo;
    novo = malloc(sizeof(Celula));
    novo->valor = num;

    if (p->prox ==  NULL)           
    {
        p->prox = novo;
        novo->prox = NULL;
    }
    else
    {
        for(p = cabeca->prox; p != NULL; p = p->prox)
        {
            if (novo->valor <= p->valor)
            {
                novo->prox = p;
                p_menos_um->prox = novo;
                break;
            }
            else if((novo->valor >= p->valor) && (p->prox == NULL))
            {
                p->prox = novo;
                novo->prox = NULL;
                break;
            }
            p_menos_um = p;
        }
    } 
}

void Pop(int num)
{
    Celula * p;
    Celula * p_menos_um = cabeca;

    for(p = cabeca->prox; p != NULL; p = p->prox)
    {
        if (p->valor == num)
        {
            p_menos_um->prox = p->prox;
            break;
        }
        p_menos_um = p;
    }
}

void List()
{
    for(Celula * p = cabeca->prox; p != NULL; p = p->prox)
    {
        printf("Valor: %d\n",p->valor);
    }
}

int main()
{
    cabeca = malloc(sizeof(Celula));
    cabeca->prox = NULL;

    PushInOrder(2);
    PushInOrder(4);
    PushInOrder(1);
    PushInOrder(10);

    Pop(10);

    List();

    return 0;
}