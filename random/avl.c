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

void Trocar(No * q, No * r)  
{
    int aux;
    if ( r->pDir == NULL )
    {
        aux = r->chave;    
        r->chave = q->chave;
        q->chave = aux; 
    }
    else
    {    
        Trocar(q, r->pDir);            
    }
}

No * RD(No * p)
{
    No * left;
    No * a;

    left = p->pEsq;
    a = left->pDir;

    left->pDir = p;
    p->pEsq = a;

    return left;
}

No * RE(No * p)
{
    No * right;
    No * a;

    right = p->pDir;
    a = right->pEsq;

    right->pEsq = p;
    p->pDir = a;
    
    return right;
}

No * Balancear(No * p)
{
    int fb = FB(p);

    if ( fb > 1 )           //desbalanceada na esquerda
    {
        fb = FB(p->pEsq);
        if (fb < 0)
        {   
            p->pEsq = RE(p->pEsq);
            return RD(p);
        }  
        else
            return RD(p); 
    }
    else if ( fb < -1 )     //desbalanceada na direita
    {
        fb = FB(p->pDir);
        if (fb > 0)
        {   
            p->pDir = RD(p->pDir);
            return RE(p);
        }  
        else
            return RE(p);       
    }
    else
    {
        return p;          //balanceada
    }
}

int Inserir(int chave, No ** p)
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
        if (chave < (*p)->chave)
        {
            Inserir(chave, &(*p)->pEsq);  
        }
        else if (chave > (*p)->chave)
        {
            Inserir(chave, &(*p)->pDir);
        }
        else if (chave == (*p)->chave)
        {
            printf("Chave ja existente na arvore\n");
            return 0;
        }
    }

    if ( (FB(*p) < -1) || (FB(*p) > 1) )
    {
        *p = Balancear(*p);
    }
    return 1;
}

No * Remover(int chave, No ** p)
{
    No * aux;

    if (*p == NULL)
    {
        printf("\nChave nao encontrada");
        return NULL;
    }
    else
    {
        if (chave < (*p)->chave)
        {
            (*p)->pEsq = Remover(chave, &(*p)->pEsq);
        }

        if (chave > (*p)->chave)
        {
            (*p)->pDir = Remover(chave, &(*p)->pDir);   
        }

        if (chave == (*p)->chave)
        {
            if ((*p)->pDir == NULL && (*p)->pEsq == NULL) { 
                free(*p);
                return NULL;
            }

            if((*p)->pDir == NULL)
            {
                aux = (*p)->pEsq;
                free(*p);
                return aux;
            }

            if((*p)->pEsq == NULL)  
            {
                aux = (*p)->pDir;
                free(*p);
                return aux;
            }

            if ( ((*p)->pEsq != NULL) &&  ((*p)->pDir != NULL) ) 
            {
                Trocar(*p, (*p)->pEsq);
                (*p)->pEsq = Remover(chave, &(*p)->pEsq);
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

    for(int i=0; i<=30; i++)
    {
        n = rand()%100;
        Inserir(n,&raiz); 
    }

    Listar(raiz,0,-1);
    return 0;
}