#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _no
{
    int chave;
    char cor;
    struct _no * pPai;
    struct _no * pEsq;
    struct _no * pDir;
} No;

void InserirCaso1(No * p);
void InserirCaso2(No * p);
void InserirCaso3(No * p);
void InserirCaso4(No * p);
void InserirCaso5(No * p);

No * raiz = NULL;

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

void RD(No * p)
{
    No * aux;
    
    if(p->pPai != NULL)                 // pai do nodo ira apontar pro filho dele
    {
        if (p->pPai->pEsq == p)         // nodo filho a esquerda
            p->pPai->pEsq = p->pEsq;
        else                            // nodo filho a direita
            p->pPai->pDir = p->pEsq;
    }
    else
    {
        raiz = p->pEsq;                 // caso o nodo a rodar for a raiz, é preciso mudar o ponteiro raiz
    }
    p->pEsq->pPai = p->pPai;            // arrumar os pais (nodo e filho)
    p->pPai = p->pEsq;                  // arrumar os pais (nodo e filho)

    aux = p->pEsq->pDir;                // rotaçao
    p->pEsq->pDir = p;
    p->pEsq = aux;
}

void RE(No * p)
{
    No * aux;

    if(p->pPai != NULL)                 // pai do nodo ira apontar pro filho dele
    {
        if (p->pPai->pEsq == p)         // nodo filho a esquerda
            p->pPai->pEsq = p->pDir;
        else                            // nodo filho a direita
            p->pPai->pDir = p->pDir;
    }
    else
    {
        raiz = p->pDir;                 // caso o nodo a rodar for a raiz, é preciso mudar o ponteiro raiz
    }
    p->pDir->pPai = p->pPai;            // arrumar os pais (nodo e filho)
    p->pPai = p->pDir;                  // arrumar os pais (nodo e filho)

    aux = p->pDir->pEsq;                // rotaçao
    p->pDir->pEsq = p;
    p->pDir = aux;    
}

No * Avo(No * p)
{
    if (p->pPai == NULL || p == NULL)
        return NULL;

    return p->pPai->pPai;
}

No * Tio(No * p)
{
    No * avo = Avo(p);

    if (avo == NULL)
        return NULL;

    if (avo->pEsq == p->pPai)
        return avo->pDir;
    else
        return avo->pEsq;
}

// A raiz sempre é preta
void InserirCaso1(No * p)   
{
    if (p->pPai == NULL)    
    {
        p->cor = 'B';
    }
    else
    {
        InserirCaso2(p);    
    }
}

// Ambos os filhos de nó preto sao vermelhos
void InserirCaso2(No * p)   
{
    if (p->pPai->cor == 'B')
    {
        return;
    }
    else
    {
        InserirCaso3(p);    
    }
}

// Tio do elemento é VERMELHO = recolorir
void InserirCaso3(No * p)   
{
    No * tio = Tio(p);
    No * avo = Avo(p);

    if (tio != NULL && tio->cor == 'R') 
    {
        p->pPai->cor = 'B';
        tio->cor = 'B';
        avo->cor = 'R';
        InserirCaso1(avo);
    }
    else
    {
        InserirCaso4(p);
    }
}

// Tio do elemento é PRETO = rotar
void InserirCaso4(No * p) 
{
    No * avo = Avo(p);

    if ( (p == p->pPai->pEsq) && (p->pPai == avo->pDir) )       //filho a esquerda
    {
        RD(p->pPai);
        p = p->pDir;
    }
    else if ( (p == p->pPai->pDir) && (p->pPai == avo->pEsq) )  //filho a direita
    {
        RE(p->pPai);
        p = p->pEsq;
    }
    InserirCaso5(p);
}

void InserirCaso5(No * p)
{
    No * avo = Avo(p);

    if ( (p == p->pPai->pEsq) && (p->pPai == avo->pEsq) )
    {     
        RD(avo);
    }
    else
    {
        RE(avo);
    }

    p->pPai->cor = 'B';
    avo->cor = 'R';
}

int Inserir(No ** p, No * pai, int chave)
{
    if (*p == NULL)
    {
        (*p) = (No*)malloc(sizeof(No));
        (*p)->chave = chave;
        (*p)->cor = 'R';
        (*p)->pPai = pai;
        (*p)->pEsq = NULL;
        (*p)->pDir = NULL;
        InserirCaso1(*p);
    }
    else
    {
        if ( chave < (*p)->chave )
        {
            return Inserir(&(*p)->pEsq,*p,chave);
        }
        else if ( chave > (*p)->chave )
        {
            return Inserir(&(*p)->pDir,*p,chave);
        }
        else if ( chave == (*p)->chave )
        {
            printf("Chave %d já existente.\n", chave);
            return 0;
        }
    }
    return 1;
}

void Listar(No * p)
{
    if (p == NULL)
        return;

    Listar(p->pEsq);
    printf("| Chave: %-4d Cor: %-4c Pai: %-4d FB: %-3d|\n",
    p->chave, p->cor, p->pPai ? p->pPai->chave : 0 ,FB(p));
    Listar(p->pDir);
}

int main()
{
    int n;
    srand(time(NULL)); 
    
    for (int i=1;i<=20;i++)
    {
        n = rand()%99;
        Inserir(&raiz,NULL,n);
    }

    Listar(raiz);
    return 0;
}