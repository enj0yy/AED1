#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
pBuffer
{
    int opcao;
    char nomePopSearch[10];
}
nodo
{
    char nome[10];
    int idade;
    int telefone;
    void * ant;
    void * prox;
}
*/

void *pBuffer = NULL;
void *head = NULL;

int ReturnOption()
{
    return *(int *)pBuffer;
}

int SizeNode()
{
    return (10 * sizeof(char)) + sizeof(int) + sizeof(int) + sizeof(void *) + sizeof(void *);
}

int SizeUntilIdade()
{
    return (10 * sizeof(char)); 
}

int SizeUntilTelefone()
{
    return SizeUntilIdade() + sizeof(int); 
}

int SizeUntilAnt()
{
    return SizeUntilTelefone() + sizeof(int); 
}

int SizeUntilProx()
{
    return SizeUntilAnt() + sizeof(void *); 
}

void Reset()
{       
    head = malloc(SizeNode());

    if (head == NULL)
    {
        printf("Nao foi possivel alocar!");
        return;
    }

    *(void **)(head + SizeUntilAnt()) = NULL;
    *(void **)(head + SizeUntilProx()) = NULL;
}

int Empty()
{
    return *(void **)(head + SizeUntilProx()) == NULL;
}

void Push()
{
    void * novo = malloc(SizeNode());
    if (novo == NULL)
    {
        printf("Nao foi possivel alocar!");
        return;
    }
    
    void * p = head;  

    printf("Digite o nome: ");
    scanf("%s",(char *)novo);

    printf("Digite a idade: ");
    scanf( "%d", (int *)(novo + SizeUntilIdade()) );

    printf("Digite o telefone: ");
    scanf( "%d", (int *)(novo + SizeUntilTelefone()) );
    
    if (Empty())    //se a lista esta vazia insere no começo
    {
        *(void **)(p + SizeUntilProx()) = novo;            
        *(void **)(novo + SizeUntilAnt()) = p;             
        *(void **)(novo + SizeUntilProx()) = NULL;   
    }
    else
    {
        p = *(void **)(head + SizeUntilProx());
        while( p != NULL ) 
        {
            if ( strcmp( (char *)novo, (char *)p ) == -1)   //se o nome a ser inserido vem antes do nome atual
            {
                *(void **)(novo + SizeUntilAnt()) = *(void **)(p + SizeUntilAnt());           
                *(void **)(novo + SizeUntilProx()) = p;

                *(void **)((*(void **)(p + SizeUntilAnt())) + SizeUntilProx()) = novo;
                *(void **)(p + SizeUntilAnt()) = novo;
                break;
            }
            else if ( (strcmp((char *)novo,(char *)p) == 1) && (*(void **)(p + SizeUntilProx()) == NULL) ) //se o nome a ser inserido vem depois do nome atual e o nome atual é o ultimo
            {
                *(void **)(p + SizeUntilProx()) = novo;            
                *(void **)(novo + SizeUntilAnt()) = p;             
                *(void **)(novo + SizeUntilProx()) = NULL; 
                break;
            }
            p = *(void **)(p + SizeUntilProx());
        }
    }         

    p = NULL;
    free(p);
}

void Pop()
{
    void * p = *(void **)(head + SizeUntilProx());   
    void * pAnt;
    void * pProx;
               
    pAnt = *(void **)(p + SizeUntilAnt());
    pProx = *(void **)(p + SizeUntilProx());

    if( pAnt != NULL )
    *(void **)(pAnt + SizeUntilProx()) = pProx;

    if( pProx != NULL )
    *(void **)(pProx + SizeUntilAnt()) = pAnt;
            
    free(p);
    printf("Primeira pessoa da fila foi apagada!");
}

void Search()
{
    void * p = *(void **)(head + SizeUntilProx());   
    printf("Digite o nome a buscar: ");
    scanf("%s",(char *)(pBuffer + sizeof(int)) );
               
    while(p!=NULL)
    {
        if ( strcmp( (char *)p, (char *)(pBuffer + sizeof(int)) ) == 0 )
        {
            printf("Nome: %s | Idade: %d | Telefone: %d\n",(char *)p, *(int *)(p + SizeUntilIdade()),*(int *)(p + SizeUntilTelefone()));
        }
        p = *(void **)(p + SizeUntilProx());
    }

    free(p); 
}

void List()
{
    void * p = *(void **)(head + SizeUntilProx());               

    while(p!=NULL)
    {
        printf("Nome: %s | Idade: %d | Telefone: %d\n",(char *)p, *(int *)(p + SizeUntilIdade()),*(int *)(p + SizeUntilTelefone()));
        p = *(void **)(p + SizeUntilProx());
    }

    free(p); 
}

void Clear()
{
    void * p = *(void **)(head + SizeUntilProx()); 
    void * nodo = *(void **)(head + SizeUntilProx());              

    while(p!=NULL)
    {
        p = *(void **)(p + SizeUntilProx());
        free(nodo); 
        nodo = (void *)(p);
    }

    free(p);
}

void Menu()
{
    do 
    {
        printf("-------------------------------------------------------\n");
        printf("1) Incluir \n2) Apagar \n3) Buscar \n4) Listar \n5) Sair\n");
        printf("-------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d",(int *)pBuffer);     
    } while(ReturnOption() < 1 || ReturnOption() > 6);
}

int main()
{
    pBuffer = malloc( sizeof(int) + (10 * sizeof(char)) ); 
    if (pBuffer == NULL)
    {
        printf("Nao foi possivel alocar!");
        return 0;
    }

    Reset();
    
    do
    {  
        Menu();
        switch (ReturnOption())
        {
        case 1:
            Push();
            break;
        case 2:
            Pop();
            break;
        case 3:
            Search();
            break;
        case 4:
            List();
            break;
        } 
    }
    while ( ReturnOption() != 5 );

    Clear();
    free(pBuffer);
    free(head);

    return 0;
}