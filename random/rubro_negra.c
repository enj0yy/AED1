#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _no
{
    int chave;
    int black;
    struct _no * pPai;
    struct _no * pEsq;
    struct _no * pDir;
} No;

void InserirCaso1(No * p);
void InserirCaso2(No * p);
void InserirCaso3(No * p);
void InserirCaso4(No * p);
void InserirCaso5(No * p);

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

No * RD(No * p)
{
    No * a;

    a = p->pEsq->pDir;

    p->pEsq->pDir = p;
    p->pEsq = a;

    return p->pEsq;
}

No * RE(No * p)
{
    No * a;

    if (p->pDir == NULL)
        a = NULL;
    else
        a = p->pDir->pEsq;

    p->pDir->pEsq = p;
    p->pDir = a;
    
    return p->pDir;
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

void InserirCaso1(No * p)   // a raiz é preta
{
    if (p->pPai == NULL)    
    {
        p->black = 1;
    }
    else
    {
        InserirCaso2(p);    
    }
}

void InserirCaso2(No * p)   // ambos os filhos de nó vermelho sao pretos
{
    if (p->pPai->black == 1)
    {
        return;
    }
    else
    {
        InserirCaso3(p);    // começa as correçoes de cores/rotacoes
    }
}

// Tio do elemento é VERMELHO = recolorir
void InserirCaso3(No * p)   
{
    No * tio = Tio(p);
    No * avo = Avo(p);

    if (tio != NULL && tio->black == 0) 
    {
        p->pPai->black = 1;
        tio->black = 1;
        avo->black = 0;
        InserirCaso1(avo);
    }
    else
    {
        InserirCaso4(p);
    }
}

// Tio do elemento é PRETO e o elemento é um filho da ESQUERDA = rota o pai pra direita
void InserirCaso4(No * p) 
{
    No * avo = Avo(p);

    if ( (p->pPai->pEsq == p) && (p->pPai == avo->pDir) )
    {
        avo->pDir = RD(p->pPai);
        p = p->pDir;
    }
    else if ( (p->pPai->pDir == p) && (p->pPai == avo->pEsq) )
    {
        avo->pEsq = RE(p->pPai);
        p = p->pEsq;
    }
    InserirCaso5(p);
}

void InserirCaso5(No * p)
{
    No * avo = Avo(p);

    if (p == p->pPai->pDir && p->pPai == avo->pDir)
    {
        if (avo == avo->pPai->pDir)
            avo->pPai->pDir = RD(avo);
        else
            avo->pPai->pEsq = RD(avo);
    }
    else
    {
        if (avo == avo->pPai->pDir)
            avo->pPai->pDir = RE(avo);
        else
            avo->pPai->pEsq = RE(avo);
    }

    p->pPai->black = 1;
    avo->black = 0;
}

int Inserir(No ** p, No * pai, int chave)
{
    if (*p == NULL)
    {
        (*p) = (No*)malloc(sizeof(No));
        (*p)->chave = chave;
        (*p)->black = 0;
        (*p)->pPai = pai;
        (*p)->pEsq = NULL;
        (*p)->pDir = NULL;
    }
    else
    {
        if ( chave < (*p)->chave )
        {
            Inserir(&(*p)->pEsq,*p,chave);
        }
        else if ( chave > (*p)->chave )
        {
            Inserir(&(*p)->pDir,*p,chave);
        }
        else if ( chave == (*p)->chave )
        {
            printf("Chave %d ja existente", chave);
            return 0;
        }
    }
    InserirCaso1(*p);
    return 1;
}

void Listar(No * p)
{
    if (p == NULL)
        return;

    Listar(p->pEsq);
    printf("| Chave: %d Preto: %d Pai-Chave: %d FB: %d|\n",p->chave,p->black, p->pPai ? p->pPai->chave : 0,FB(p));
    Listar(p->pDir);
}

int main()
{
    No * raiz = NULL;
    Inserir(&raiz,NULL,10);
    Inserir(&raiz,NULL,5);
    Inserir(&raiz,NULL,15);
    Inserir(&raiz,NULL,3);
    Inserir(&raiz,NULL,2);
    Inserir(&raiz,NULL,1);
    Listar(raiz);
    return 0;
}