// Graziele Fagundes Martins - M1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
Estrutura:

pBuffer
{
    int opcao;
    char nomeApagarProcurar[10];
    char nome[10];
    int idade;
    int telefone;
}

Pessoa
{
    char nome[10];
    int idade;
    int telefone;
    void * anterior;
    void * proximo;
}

*/

void *pBuffer = NULL;

int ReturnOption()
{
    return *(int *)pBuffer;
}

int SizePerson()
{
    return ( 10 * sizeof(char) ) + sizeof(int) + sizeof(int) + sizeof(void *) + sizeof(void *);
}

int SizeUntilAge()
{
    return ( 10 * sizeof(char) ); 
}

int SizeUntilTelephone()
{
    return SizeUntilAge() + sizeof(int); 
}

int SizeUntilPrevious()
{
    return SizeUntilTelephone() + sizeof(int); 
}

int SizeUntilNext()
{
    return SizeUntilPrevious() + sizeof(void *); 
}

int Empty( void * head )
{
    return *(void **)( head + SizeUntilNext() ) == NULL;
}

void * Reset()
{       
    void * head = malloc( SizePerson() );

    if (head == NULL)
    {
        printf("Nao foi possivel alocar!\n");
        return 0;
    }

    *(void **)( head + SizeUntilPrevious() ) = NULL;
    *(void **)( head + SizeUntilNext() ) = NULL;

    return head;
}

void * ResetPBuffer()
{       
    void * pb = malloc( sizeof(int) + (10 * sizeof(char)) + (10 * sizeof(char)) + (sizeof(int))*2 ); 

    if (pb == NULL)
    {
        printf("Nao foi possivel alocar!\n");
        return 0;
    }

    return pb;
}

void AskQuestions( char * name, int * age, int * telephone )
{
    printf("Digite o nome: ");
    scanf( "%s", name );

    printf("Digite a idade: ");
    scanf( "%d", age );

    printf("Digite o telefone: ");
    scanf( "%d", telephone );
}

void * NewPerson( char * name, int * age, int * telephone )
{
    void * newPerson = malloc( SizePerson() );
    if (newPerson == NULL)
    {
        printf("Nao foi possivel alocar!\n");
        return 0;
    }
    
    strcpy( newPerson, name );
    *(int *)( newPerson + SizeUntilAge() ) = *age;
    *(int *)( newPerson + SizeUntilTelephone() ) = *telephone;
    *(void **)( newPerson + SizeUntilPrevious() ) = NULL;
    *(void **)( newPerson + SizeUntilNext() ) = NULL;

    return newPerson;
}

void Push( void * head, void * person )
{
    void * p;  
    
    if ( Empty(head) )    //se a agenda está vazia insere no começo
    {
        *(void **)( head + SizeUntilNext() ) = person;            
        *(void **)( person + SizeUntilPrevious() ) = head;             
        *(void **)( person + SizeUntilNext() ) = NULL;   
    }
    else
    {
        p = *(void **)( head + SizeUntilNext() );

        while( p != NULL ) 
        {
            if ( strcmp( (char *)person, (char *)p ) <= 0 )     //se o nome a ser inserido vem antes do nome atual ou se é igual
            {
                *(void **)( person + SizeUntilPrevious() ) = *(void **)( p + SizeUntilPrevious() );           
                *(void **)( person + SizeUntilNext() ) = p;

                *(void **)( (*(void **)(p + SizeUntilPrevious())) + SizeUntilNext() ) = person;
                *(void **)( p + SizeUntilPrevious() ) = person;

                break;
            }
            else if ( ( strcmp((char *)person, (char *)p) > 0 ) && ( *(void **)(p + SizeUntilNext()) == NULL ) )    //se o nome a ser inserido vem depois do nome atual e o nome atual é o ultimo
            {
                *(void **)( p + SizeUntilNext() ) = person;            
                *(void **)( person + SizeUntilPrevious() ) = p;             
                *(void **)( person + SizeUntilNext() ) = NULL; 

                break;
            }
            p = *(void **)( p + SizeUntilNext() );
        }
    }         
}

int Pop( void * head )
{
    if ( !Empty(head) )
    {
        void * pop = *(void **)( head + SizeUntilNext() );              //a pessoa a ser removida é a primeira da fila 
        void * pNextPop = *(void **)( pop + SizeUntilNext() );          //a pessoa que vem após a primeira da fila
            
        if( head != NULL )
        *(void **)( head + SizeUntilNext() ) = pNextPop;                //a cabeça aponta para a pessoa que vem após a primeira da fila

        if( pNextPop != NULL )
        *(void **)( pNextPop + SizeUntilPrevious() ) = head;            //o ponteiro anterior da pessoa que vem após a primeira da fila aponta para cabeça
                
        //guardar as informacoes da pessoa removida no pBuffer para caso precise acessar as informaçoes dela
        strcpy( (pBuffer + sizeof(int) + (10 * sizeof(char))), pop );
        *(int*)( pBuffer + sizeof(int) + (10 * sizeof(char))*2 ) = *(int*)( pop + SizeUntilAge() );
        *(int*)( pBuffer + sizeof(int) + (10 * sizeof(char))*2 + sizeof(int) ) = *(int*)( pop + SizeUntilTelephone() );
        
        free(pop);                                                      //finalmente free na pessoa
        return 1;
    } 
    else
    {
       printf("Agenda vazia!\n"); 
       return 0;
    }
}

void DeleteByName( void * head )
{  
    printf("Digite o nome a apagar: ");
    scanf( "%s", (char *)(pBuffer + sizeof(int)) );                       //guarda nome no pBuffer para comparaçao

    void * headTemp = NULL;                                               //agenda temporária para guardar as pessoas retiradas da agenda principal
    headTemp = Reset();

    char * name = ( pBuffer + sizeof(int) + (10 * sizeof(char)) );        //ponteiros para dentro do pBuffer que guardam as informaçoes da pessoa que foi apagada no pop
    int * age = ( pBuffer + sizeof(int) + (10 * sizeof(char))*2 );
    int * telephone = ( pBuffer + sizeof(int) + (10 * sizeof(char))*2 + sizeof(int) ); 
               
    while( !Empty(head) )
    {
        Pop(head);                      
        if ( strcmp( name, (char *)(pBuffer + sizeof(int)) ) == 0 )       //se nome pop == nome a apagar: nao insere na agenda temporária
        {
            printf("Pessoa apagada!\n");                              
        }
        else
        {
            Push(headTemp,NewPerson(name,age,telephone));                 //se nome pop != nome a apagar: insere na agenda temporária
        }
    }  

    while( !Empty(headTemp) )                                             //insere de volta as pessoas da agenda temporária para a agenda principal
    {
        Pop(headTemp);
        Push(head,NewPerson(name,age,telephone));
    }

    free(headTemp);
}

void SearchByName( void * head )
{
    printf("Digite o nome a buscar: ");
    scanf( "%s", (char *)(pBuffer + sizeof(int)) );                         //guarda nome no pBuffer para comparaçao

    void * headTemp = NULL;                                                 //agenda temporária para guardar as pessoas retiradas da agenda principal
    headTemp = Reset();

    char * name = ( pBuffer + sizeof(int) + (10 * sizeof(char)) );          //ponteiros para dentro do pBuffer que guardam as informaçoes da pessoa que foi apagada no pop
    int * age = ( pBuffer + sizeof(int) + (10 * sizeof(char))*2 );
    int * telephone = ( pBuffer + sizeof(int) + (10 * sizeof(char))*2 + sizeof(int) ); 
               
    while( !Empty(head) )
    {
        Pop(head);
        Push(headTemp,NewPerson(name,age,telephone));
        if ( strcmp( name, (char *)(pBuffer + sizeof(int)) ) == 0 )         //se nome pop == nome a buscar: imprime informacoes
        {
            printf("Informacoes de %s: \n", name);
            printf("Nome: %-10s| Idade: %-3d | Telefone: %d\n", name, *age, *telephone);      
        } 
    }  

    while( !Empty(headTemp) )                                               //insere de volta as pessoas da agenda temporária para a agenda principal
    {
        Pop(headTemp);
        Push(head,NewPerson(name,age,telephone));
    }

    free(headTemp);
}

void List( void * head )
{   
    void * headTemp = NULL;                                                 //agenda temporária para guardar as pessoas retiradas da agenda principal
    headTemp = Reset();

    char * name = ( pBuffer + sizeof(int) + (10 * sizeof(char)) );          //ponteiros para dentro do pBuffer que guardam as informaçoes da pessoa que foi apagada no pop
    int * age = ( pBuffer + sizeof(int) + (10 * sizeof(char))*2 );
    int * telephone = ( pBuffer + sizeof(int) + (10 * sizeof(char))*2 + sizeof(int) );            

    while( !Empty(head) )
    {
        Pop(head);
        Push(headTemp,NewPerson(name,age,telephone));
        printf("Nome: %-10s| Idade: %-3d | Telefone: %d\n", name, *age, *telephone);
    }

    while( !Empty(headTemp) )                                               //insere de volta as pessoas da agenda temporária para a agenda principal
    {
        Pop(headTemp);
        Push(head,NewPerson(name,age,telephone));
    }

    free(headTemp);
}

void Clear( void * head )
{
    while( !Empty(head) )             
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
        scanf( "%d", (int *)pBuffer );     
    } while( ReturnOption() < 1 || ReturnOption() > 6 );
}

int main()
{
    void * head = NULL;
    head = Reset();

    pBuffer = ResetPBuffer();

    char * name = ( pBuffer + sizeof(int) + (10 * sizeof(char)) );        
    int * age = ( pBuffer + sizeof(int) + (10 * sizeof(char))*2 );
    int * telephone = ( pBuffer + sizeof(int) + (10 * sizeof(char))*2 + sizeof(int) );

    do
    {  
        Menu();
        switch ( ReturnOption() )
        {
        case 1:
            AskQuestions(name,age,telephone);
            Push(head,NewPerson(name,age,telephone));
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
