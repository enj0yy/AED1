#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _no
{
    int chave;
    struct _no * pEsq;
    struct _no * pDir;
} No;

int Altura(No * p)
{
    int esq,dir;

    if (p == NULL)
        return 0;

    esq = Altura(p->pEsq);
    dir = Altura(p->pDir);

    if (esq > dir)
        return 1 + esq;
    else
       return 1 + dir; 
}

int FB(No * p)
{
    if (p == NULL)
    return 0;

    return Altura(p->pEsq) - Altura(p->pDir);
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
        return *p;
    } 
}

void Listar(No * p, int level, int isleft)
{
    if (p == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf(i == level-1 ? "|_" : "  ");

    switch (isleft)
    {
    case -1:
        printf("r(%d) FB(%d)\n", p->chave, FB(p));
        break;
    case 1:
        printf("e(%d) FB(%d)\n", p->chave, FB(p));
        break;
    case 0:
        printf("d(%d) FB(%d)\n", p->chave, FB(p));
        break;
    }
    
    Listar(p->pEsq, level+1, 1);
    Listar(p->pDir, level+1, 0);
}

int main()
{
    int n;
    No * raiz = NULL;
    srand(time(NULL)); 

    for(int i=0; i<=5; i++)
    {
        n = rand()%100;
        Inserir(n,&raiz); 
    }
    
    printf("Pre ordem:\n");
    Listar(raiz,0,-1);


    return 0;
}