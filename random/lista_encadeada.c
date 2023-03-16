#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cel
{
    int valor;
    struct cel * prox;
} Celula;

Celula * cabeca;

void InserirNoFinal(int num)
{
    Celula * p;

    Celula * novo;
    novo = malloc(sizeof(Celula));
    novo->valor = num;
    novo->prox = NULL;

    for(p = cabeca; p->prox != NULL; p = p->prox);
    p->prox = novo;
}

void InserirOrdenado(int num)
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

void Remover(int num)
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

void Listar()
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

    InserirOrdenado(2);
    InserirOrdenado(4);
    InserirOrdenado(1);
    InserirOrdenado(10);

    Remover(10);

    Listar();

    return 0;
}