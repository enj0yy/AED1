#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
Estrutura:

pBuffer
{
    int opcao;
    char nomeDeleteSearch[10];
    char nome[10];
    int idade;
    int telefone;
}

pessoa
{
    char nome[10];
    int idade;
    int telefone;
    void * ant;
    void * prox;
}

*/

void *pBuffer = NULL;

int ReturnOption()
{
    return *(int *)pBuffer;
}

int SizePessoa()
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

int Empty(void * head)
{
    return *(void **)(head + SizeUntilProx()) == NULL;
}

void * Reset()
{       
    void * head = malloc(SizePessoa());

    if (head == NULL)
    {
        printf("Nao foi possivel alocar!\n");
        return 0;
    }

    *(void **)(head + SizeUntilAnt()) = NULL;
    *(void **)(head + SizeUntilProx()) = NULL;

    return head;
}

void * ResetPBuffer()
{       
    void * pb = malloc( sizeof(int) + (10 * sizeof(char))*2 + (sizeof(int))*2 ); 

    if (pb == NULL)
    {
        printf("Nao foi possivel alocar!\n");
        return 0;
    }

    return pb;
}

void AskQuestions(char * nome, int * idade, int * telefone)
{
    printf("Digite o nome: ");
    scanf( "%s", nome );

    printf("Digite a idade: ");
    scanf( "%d", idade );

    printf("Digite o telefone: ");
    scanf( "%d", telefone );
}

void * NewPerson(char * nome, int * idade, int * telefone)
{
    void * nova_pessoa = malloc(SizePessoa());
    if (nova_pessoa == NULL)
    {
        printf("Nao foi possivel alocar!\n");
        return 0;
    }
    
    strcpy(nova_pessoa, nome);
    *(int *)(nova_pessoa + SizeUntilIdade()) = *idade;
    *(int *)(nova_pessoa + SizeUntilTelefone()) = *telefone;
    *(void **)(nova_pessoa + SizeUntilAnt()) = NULL;
    *(void **)(nova_pessoa + SizeUntilProx()) = NULL;

    return nova_pessoa;
}

void Push(void * head, void * pessoa)
{
    void * p = head;  
    
    if (Empty(head))    //se a agenda está vazia insere no começo
    {
        *(void **)(p + SizeUntilProx()) = pessoa;            
        *(void **)(pessoa + SizeUntilAnt()) = p;             
        *(void **)(pessoa + SizeUntilProx()) = NULL;   
    }
    else
    {
        p = *(void **)(head + SizeUntilProx());
        while( p != NULL ) 
        {
            if ( strcmp( (char *)pessoa, (char *)p ) == -1)   //se o nome a ser inserido vem antes do nome atual
            {
                *(void **)(pessoa + SizeUntilAnt()) = *(void **)(p + SizeUntilAnt());           
                *(void **)(pessoa + SizeUntilProx()) = p;

                *(void **)((*(void **)(p + SizeUntilAnt())) + SizeUntilProx()) = pessoa;
                *(void **)(p + SizeUntilAnt()) = pessoa;
                break;
            }
            else if ( (strcmp((char *)pessoa,(char *)p) == 1) && (*(void **)(p + SizeUntilProx()) == NULL) ) //se o nome a ser inserido vem depois do nome atual e o nome atual é o ultimo
            {
                *(void **)(p + SizeUntilProx()) = pessoa;            
                *(void **)(pessoa + SizeUntilAnt()) = p;             
                *(void **)(pessoa + SizeUntilProx()) = NULL; 
                break;
            }
            p = *(void **)(p + SizeUntilProx());
        }
    }         

    p = NULL;
    free(p);
}

int Pop(void * head)
{
    if (!Empty(head))
    {
        void * pop = *(void **)(head + SizeUntilProx());        //a pessoa a ser removida é a primeira da fila 
        void * pProxPop = *(void **)(pop + SizeUntilProx());    //a pessoa que vem após a primeira da fila
            
        if( head != NULL )
        *(void **)(head + SizeUntilProx()) = pProxPop;          //a cabeça aponta para a pessoa que vem após a primeira da fila

        if( pProxPop != NULL )
        *(void **)(pProxPop + SizeUntilAnt()) = head;           //o ponteiro anterior da pessoa que vem após a primeira da fila aponta para cabeça
                
        //guardar as informacoes da pessoa removida no pBuffer para caso precise acessar as informaçoes dela
        strcpy((pBuffer + sizeof(int) + (10 * sizeof(char))),pop);
        *(int*)(pBuffer + sizeof(int) + (10 * sizeof(char))*2) = *(int*)(pop + SizeUntilIdade());
        *(int*)(pBuffer + sizeof(int) + (10 * sizeof(char))*2 + sizeof(int)) = *(int*)(pop + SizeUntilTelefone());
        
        free(pop);
        return 1;
    } else
    {
       printf("Agenda vazia!\n"); 
       return 0;
    }
}

void DeleteByName(void * head)
{  
    printf("Digite o nome a apagar: ");
    scanf("%s",(char *)(pBuffer + sizeof(int)) );                    //guarda nome no pBuffer para comparaçao

    void * head_temp = NULL;                                         //agenda temporária para guardar as pessoas retiradas da agenda principal
    head_temp = Reset();

    char * nome = (pBuffer + sizeof(int) + (10 * sizeof(char)));     //ponteiros para dentro do pBuffer que guardam as informaçoes da pessoa que foi apagada no pop
    int * idade = (pBuffer + sizeof(int) + (10 * sizeof(char))*2);
    int * telefone = (pBuffer + sizeof(int) + (10 * sizeof(char))*2 + sizeof(int)); 
               
    while(!Empty(head))
    {
        Pop(head);                      
        if ( strcmp( nome, (char *)(pBuffer + sizeof(int)) ) == 0 )   //se nome pop == nome a apagar
        {
            printf("Pessoa apagada :)\n");                            //nao insere na agenda temporária
        }
        else
        {
            Push(head_temp,NewPerson(nome,idade,telefone));           //se nome pop != nome a apagar insere na agenda temporária
        }
    }  

    while(!Empty(head_temp))                                          //insere de volta as pessoas da agenda temporária para a agenda principal
    {
        Pop(head_temp);
        Push(head,NewPerson(nome,idade,telefone));
    }
    free(head_temp);
}

void SearchByName(void * head)
{
    printf("Digite o nome a buscar: ");
    scanf("%s",(char *)(pBuffer + sizeof(int)) );                   //guarda nome no pBuffer para comparaçao

    void * head_temp = NULL;                                        //agenda temporária para guardar as pessoas retiradas da agenda principal
    head_temp = Reset();

    char * nome = (pBuffer + sizeof(int) + (10 * sizeof(char)));    //ponteiros para dentro do pBuffer que guardam as informaçoes da pessoa que foi apagada no pop
    int * idade = (pBuffer + sizeof(int) + (10 * sizeof(char))*2);
    int * telefone = (pBuffer + sizeof(int) + (10 * sizeof(char))*2 + sizeof(int)); 
               
    while(!Empty(head))
    {
        Pop(head);
        Push(head_temp,NewPerson(nome,idade,telefone));
        if ( strcmp( nome, (char *)(pBuffer + sizeof(int)) ) == 0 )                         //se nome pop == nome a apagar
        {
            printf("Nome: %s | Idade: %d | Telefone: %d\n", nome, *idade, *telefone);       //imprime informacoes
        } 
    }  

    while(!Empty(head_temp))                                                                //insere de volta as pessoas da agenda temporária para a agenda principal
    {
        Pop(head_temp);
        Push(head,NewPerson(nome,idade,telefone));
    }
    free(head_temp);
}

void List(void * head)
{   
    void * head_temp = NULL;                                        //agenda temporária para guardar as pessoas retiradas da agenda principal
    head_temp = Reset();

    char * nome = (pBuffer + sizeof(int) + (10 * sizeof(char)));    //ponteiros para dentro do pBuffer que guardam as informaçoes da pessoa que foi apagada no pop
    int * idade = (pBuffer + sizeof(int) + (10 * sizeof(char))*2);
    int * telefone = (pBuffer + sizeof(int) + (10 * sizeof(char))*2 + sizeof(int));            

    while(!Empty(head))
    {
        Pop(head);
        Push(head_temp,NewPerson(nome,idade,telefone));
        printf("Nome: %s | Idade: %d | Telefone: %d\n", nome, *idade, *telefone);
    }

    while(!Empty(head_temp))                                        //insere de volta as pessoas da agenda temporária para a agenda principal
    {
        Pop(head_temp);
        Push(head,NewPerson(nome,idade,telefone));
    }

    free(head_temp);
}

void Clear(void * head)
{
    while(!Empty(head))     //remove todas pessoas da agenda         
    {
        Pop(head);      
    }
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
    void * head = NULL;
    head = Reset();

    pBuffer = ResetPBuffer();

    char * nome = (pBuffer + sizeof(int) + (10 * sizeof(char)));        
    int * idade = (pBuffer + sizeof(int) + (10 * sizeof(char))*2);
    int * telefone = (pBuffer + sizeof(int) + (10 * sizeof(char))*2 + sizeof(int));

    do
    {  
        Menu();
        switch (ReturnOption())
        {
        case 1:
            AskQuestions(nome,idade,telefone);
            Push(head,NewPerson(nome,idade,telefone));
            break;
        case 2:
            DeleteByName(head);
            break;
        case 3:
            SearchByName(head);
            break;
        case 4:
            List(head);
            break;
        } 
    }
    while ( ReturnOption() != 5 );

    Clear(head);
    free(head);
    free(pBuffer);

    return 0;
}
