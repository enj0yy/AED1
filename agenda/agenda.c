#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
pBuffer
{
    int opcao;
    char nomeBuscar[10];
}
nodo
{
    char nome[10];
    int idade;
    int telefone;
    char * ant;
    char * prox;
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
    void * p = head;  

    printf("Digite o nome: ");
    scanf("%s",(char *)novo);

    printf("Digite a idade: ");
    scanf( "%d", (int *)(novo + SizeUntilIdade()) );

    printf("Digite o telefone: ");
    scanf( "%d", (int *)(novo + SizeUntilTelefone()) );

    while( *(void **)(p + SizeUntilProx()) != NULL )    //anda na lista até achar o nodo que tem prox == NULL, o ultimo
    {
         p = *(void **)(p + SizeUntilProx());
    }
    *(void **)(p + SizeUntilProx()) = novo;      //proximo - anterior ao novo  
    *(void **)(novo + SizeUntilAnt()) = p;       //anterior - novo
    *(void **)(novo + SizeUntilProx()) = NULL;   //proximo - novo

    free(p);
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
            printf("Nome: %s\n",(char *)p);
            printf("Idade: %d\n",*(int *)(p + SizeUntilIdade()));
            printf("Telefone: %d\n",*(int *)(p + SizeUntilTelefone()));
        }
        p = *(void **)(p + SizeUntilProx());
    }

    free(p);
}

void List()
{
    void * p = *(void **)(head + SizeUntilProx());                //comeca no proximo da cabeca

    while(p!=NULL)
    {
        printf("Nome: %s\n",(char *)p);
        printf("Idade: %d\n",*(int *)(p + SizeUntilIdade()));
        printf("Telefone: %d\n",*(int *)(p + SizeUntilTelefone()));

        p = *(void **)(p + SizeUntilProx());
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
            //Pop();
            break;
        case 3:
            Search();
            break;
        case 4:
            List();
            break;
        } 
    }
    while ( ReturnOption() != 5);

    free(pBuffer);

    return 0;
}