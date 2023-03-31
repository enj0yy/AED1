#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _no
{
    int chave;
    struct _no * pEsq;
    struct _no * pDir;
} No;

int Altura(No * p, No * raiz)
{
    if (raiz == p)
        return 1;

    if(p->chave < raiz->chave)
        return 1 + Altura(p,raiz->pEsq);
    else 
        return 1 + Altura(p,raiz->pDir);
}

void Inserir(int chave, No ** p)
{
    if (*p == NULL)
    {
        (*p) = malloc(sizeof(No));
        (*p)->chave = chave;
        (*p)->pEsq = NULL;
        (*p)->pDir = NULL;
    }
    else
    {
        if(chave < (*p)->chave)
        {
            Inserir(chave,&(*p)->pEsq);
        }
        else if(chave > (*p)->chave)
        {
            Inserir(chave,&(*p)->pDir);
        }
    }
}

int Pesquisar(int chave, No ** p)
{
    if (*p == NULL)
    {
        printf("\nRegistro %d nao encontrado.",chave);
        return 0;
    }
    else
    {
        if(chave == (*p)->chave)
        {
            printf("\nRegistro %d encontrado.",chave);
            return 1;
        }

        if(chave < (*p)->chave)
        {
            Pesquisar(chave,&(*p)->pEsq);
        }
        else if(chave > (*p)->chave)
        {
            Pesquisar(chave,&(*p)->pDir);
        }
        return 0;
    }  
}

void Trocar(No * q, No ** r)  
{
    int aux;

    if ( (*r)->pDir != NULL )
    {
        Trocar(q, &(*r)->pDir); 
    }
    else
    {    
        aux = (*r)->chave;      // troca a chave de quem vai ser apagado com folha
        (*r)->chave = q->chave;
        q->chave = aux;            
    }
}

No * Retirar(int chave, No ** p)
{
    No * Aux;

    if (*p == NULL)
    {
        printf("\nRegistro %d nao encontrado.",chave);
        return NULL;
    }
    else
    {
        if(chave < (*p)->chave)
        {
            (*p)->pEsq = Retirar(chave,&(*p)->pEsq);
        }
        else if(chave > (*p)->chave)
        {
            (*p)->pDir = Retirar(chave,&(*p)->pDir);
        }

        if(chave == (*p)->chave)
        {
            if ((*p)->pDir == NULL && (*p)->pEsq == NULL) { // folha
                free(*p);
                return NULL;
            }

            if ((*p)->pDir == NULL) { // tem só 1 filho a esquerda
                Aux = (*p)->pEsq; 
                free(*p);
                return Aux;
            }

            if ((*p)->pEsq == NULL) { // tem só 1 filho a direita
                Aux = (*p)->pDir; 
                free(*p);
                return Aux;
            }   

            if ( ((*p)->pEsq != NULL) &&  ((*p)->pDir != NULL) ) // tem 2 filhos
            {
                Trocar(*p, &(*p)->pEsq);                         //troca os valores do que é a ser excluido com o mais a direita da sub arvore a esquerda
                (*p)->pEsq = Retirar(chave, &(*p)->pEsq);        //retirar o nodo agora que é uma folha ou so tem no maximo um filho
                return *p;
            }            
        }

        return NULL;
    } 
}

void Listar(No * p, No * raiz, int isleft)
{
    if (p == NULL)
        return;

    for (int i = 0; i < Altura(p,raiz) - 1; i++)
        printf(i == Altura(p,raiz) - 2 ? "|_" : "| ");

    switch (isleft)
    {
    case -1:
        printf("r(%d)\n", p->chave);
        break;
    case 1:
        printf("e(%d)\n", p->chave);
        break;
    case 0:
        printf("d(%d)\n", p->chave);
        break;
    }

    Listar(p->pEsq, raiz, 1);
    Listar(p->pDir, raiz, 0);
}

int main()
{
    No * raiz = NULL;
    Inserir(10, &raiz);
    Inserir(8, &raiz);
    Inserir(11, &raiz);
    Inserir(7, &raiz);
    Inserir(9, &raiz);

    printf("Pre ordem:\n");
    Listar(raiz,raiz,-1);

    Retirar(8,&raiz);

    printf("\nPre ordem:\n");
    Listar(raiz,raiz,-1);

    return 0;
}