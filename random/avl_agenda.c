#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[10];
    int idade;
    int telefone;
} Pessoa;

typedef struct _no
{
    Pessoa pessoa;
    struct _no * pEsq;
    struct _no * pDir;
} No;

int Altura(No * p)
{
    int esq, dir;

    if ( p == NULL )
        return 1;

    esq = Altura(p->pEsq);
    dir = Altura(p->pDir);

    if ( esq > dir )
        return 1 + esq;
    else
        return 1 + dir;
}

int FB(No * p)
{
    return Altura(p->pEsq) - Altura(p->pDir);
}

No * RD(No * p)
{
    No * a;
    No * left;

    left = p->pEsq;
    a = left->pDir;
    
    left->pDir = p;
    p->pEsq = a;

    return left;
}

No * RE(No * p)
{
    No * a;
    No * right;

    right = p->pDir;
    a = right->pEsq;

    right->pEsq = p;
    p->pDir = a;

    return right;
}

No * Balancear( No * p)
{
    int fb = FB(p);

    if (fb >= -1 && fb <= 1)    //balanceada
    {
        return p;
    }
    else
    {
        if ( fb > 1 )                       // desbalanceada na esquerda (fb > 1)
        {
            fb = FB(p->pEsq);
            if ( fb >= 1 ) 
            {
                return RD(p);
            }
            else                            // ( fb <= -1 )
            {
                p->pEsq = RE(p->pEsq);
                return RD(p);
            }
        }
        else                                // desbalanceada na direita (fb < -1)
        {
            fb = FB(p->pDir);
            if ( fb <= -1 ) 
            {
                return RE(p);
            }
            else                            // ( fb >= 1 )
            {
                p->pDir = RD(p->pDir);
                return RE(p);
            }
        }
    }
}

int Inserir(No ** p, Pessoa pessoa)
{
    if (*p == NULL)
    {
        *p = (No*)malloc(sizeof(No));
        (*p)->pessoa = pessoa;
        (*p)->pEsq = NULL;
        (*p)->pDir = NULL;
        return 1;
    }
    else
    {
        if (strcmp(pessoa.nome,(*p)->pessoa.nome) < 0)
        {
            Inserir(&(*p)->pEsq,pessoa);
        }
        else if (strcmp(pessoa.nome,(*p)->pessoa.nome) > 0)
        {
            Inserir(&(*p)->pDir,pessoa);
        }
        else
        {
            printf("Pessoa ja esta presente na agenda!\n");
            return 0;
        }
        *p = Balancear(*p);
        return 1;
    }
}

void Trocar(No * p, No * pDir)
{
    Pessoa pessoaAux;

    if (pDir->pDir == NULL)
    {
        pessoaAux = p->pessoa;
        p->pessoa = pDir->pessoa;
        pDir->pessoa = pessoaAux;
    }
    else
    {
        Trocar(p,pDir->pDir);
    }
}

int Remover(No ** p, char nome[])
{
    No * aux;

    if (*p == NULL)
    {
        printf("Pessoa nao encontrada!\n");
        return 0;
    }
    else
    {
        if (strcmp(nome,(*p)->pessoa.nome) < 0)
        {
            Remover(&(*p)->pEsq,nome);
            *p = Balancear(*p);
        }
        else if (strcmp(nome,(*p)->pessoa.nome) > 0)
        {
            Remover(&(*p)->pDir,nome);
            *p = Balancear(*p);
        }
        else if (strcmp(nome,(*p)->pessoa.nome) == 0)
        {
            if ( (*p)->pEsq == NULL && (*p)->pDir == NULL )     // folha
            {
                *p = NULL;
                free(*p);
            }
            else if ( (*p)->pDir == NULL )                      // 1 filho na esquerda
            {
                aux = *p;
                *p = (*p)->pEsq;
                free(aux);
            }
            else if ( (*p)->pEsq == NULL )                      // 1 filho na direita
            {
                aux = *p;
                *p = (*p)->pDir;
                free(aux);
            }
            else                                                // 2 filhos
            {
                Trocar(*p, (*p)->pEsq);
                Remover(&(*p)->pEsq, nome);
            }
        }
        return 1;
    } 
}

void Listar(No * p, int ERaiz)
{
    if (p == NULL)
        return;
    
    Listar(p->pEsq,0);
    printf("%s Nome: %-10s Idade: %-3d Telefone: %-3d FB: %-2d\n",ERaiz ? "R" : " ",p->pessoa.nome,p->pessoa.idade,p->pessoa.telefone,FB(p));
    Listar(p->pDir,0);
}

No * LimparArvore(No * p)
{
    if ( p == NULL )
        return NULL;

    p->pEsq = LimparArvore(p->pEsq);
    p->pEsq = LimparArvore(p->pDir);
    free(p);

    return NULL;
}

int EhAVL(No * p)
{
    int fb;
    
    if ( p == NULL )
    {
        return 1;
    }
    
    fb = FB(p);
    if ( fb >= -1 && fb <= 1 )                      // esse nodo é balanceado
    {
        return EhAVL(p->pDir) && EhAVL(p->pEsq);    // testa se as subarvores deles sao tambem
    }
    else
    {
        return 0;
    }
}

int main()
{
    No * raiz = NULL;
    Pessoa pessoa;
    int choice;

    do
    {
        printf("1) Inserir \n2) Remover \n3) Listar \n4) Sair");
        printf("\nDigite a opcao: ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            printf("Nome: ");
            scanf("%s",pessoa.nome);
            printf("Idade: ");
            scanf("%d",&pessoa.idade);
            printf("Telefone: ");
            scanf("%d",&pessoa.telefone);
            Inserir(&raiz,pessoa);
            break;
        case 2:
            printf("Nome: ");
            scanf("%s",pessoa.nome);
            Remover(&raiz,pessoa.nome);
            break;
        case 3:    
            printf("------------------------------------------------------\n");
            printf("Ordem central: \n");
            Listar(raiz,1);
            printf("------------------------------------------------------\n");
            break;
        case 4:
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (choice != 4);
    
    printf("E AVL? %s", EhAVL(raiz) ? "Sim" : "Nao");
    raiz = LimparArvore(raiz);

    return 0;
}