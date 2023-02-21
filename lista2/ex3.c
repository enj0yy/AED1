/* Faça uma agenda capaz de incluir, apagar, buscar e listar
quantas pessoas o usuário desejar, porém, toda a informação
incluída na agenda deve ficar num único lugar chamado: “void
*pBuffer”. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *pBuffer = NULL;
const int tamanho_pessoa = (10 * sizeof(char)) + (sizeof(int)) + sizeof(int);

int Menu()
{
    int opcao;
    do 
    {
        printf("-------------------------------------------------------\n");
        printf("1) Incluir \n2) Apagar \n3) Buscar \n4) Listar \n5) Sair\n");
        printf("-------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d",&opcao);     
    } while(opcao < 1 || opcao > 6);
    return opcao;
}

void Incluir()
{
    char nome[10];
    int idade;
    int telefone;
    int n_pessoas;

    getchar();
    printf("Nome: ");
    gets(nome);
    printf("Idade: ");
    scanf("%d",&idade);
    printf("Telefone: ");
    scanf("%d",&telefone);
 
    *((int*)pBuffer) += 1;
    n_pessoas = *((int*)pBuffer);

    pBuffer = realloc(pBuffer, sizeof(int) + (tamanho_pessoa * n_pessoas));
    
    pBuffer += sizeof(int);                             //Pula o n_pessoas
    pBuffer += (n_pessoas-1) * tamanho_pessoa;          //Pula as pessoas ja existentes

    strcpy(pBuffer,nome);                               //seta o nome
    pBuffer += (10 * sizeof(char));                     //Pula o nome

    *(int*)pBuffer = idade;                             //Seta a idade                                                                                                           
    pBuffer += sizeof(int);                             //Pula a idade   

    *(int*)pBuffer = telefone;                          //Seta o telefone                                                           

    pBuffer -= tamanho_pessoa * (n_pessoas);            //Seta ponteiro pro inicio
}

void Apagar()
{
    int qtde_apagados = 0;
    char nome[10];
    getchar();
    printf("Nome a apagar: ");
    gets(nome);

    int n_pessoas = *((int*)pBuffer);
    pBuffer += sizeof(int);                                 

    for(int i=1;i<=n_pessoas;i++)
    {
        if (strcmp(nome,(char*)pBuffer) == 0)
        {
            if (n_pessoas > 1)                                                          //se tem somente uma pessoa nao precisa mover o restante das pessoas
                memcpy(pBuffer,(pBuffer+tamanho_pessoa),(n_pessoas-i)*tamanho_pessoa);
            qtde_apagados++;
        }
        pBuffer += tamanho_pessoa;
    }
    pBuffer -= (tamanho_pessoa * n_pessoas) + sizeof(int);
    if(qtde_apagados)
    {
        *((int*)pBuffer) -= qtde_apagados;   
        pBuffer = realloc(pBuffer, sizeof(int) + (tamanho_pessoa * (n_pessoas-qtde_apagados)));  
    }       
}

void Buscar()
{
    char nome[10];
    getchar();
    printf("Nome a buscar: ");
    gets(nome);

    int n_pessoas = *((int*)pBuffer);
    pBuffer += sizeof(int);                             //Pula o n_pessoas

    for(int i=0;i<n_pessoas;i++)
    {
        if (strcmp(nome,(char*)pBuffer) == 0)
        {
            printf("Nome: %s\n", (char*)pBuffer);       //Mostra nome
            pBuffer += (10 * sizeof(char));             //Pula o nome
            printf("Idade: %d\n", *(int*)pBuffer);      //Mostra idade
            pBuffer += sizeof(int);                     //Pula a idade
            printf("Telefone: %d\n", *(int*)pBuffer);   //Mostra telefone
            pBuffer += sizeof(int);                     //Pula o telefone
        }
        else
        {
            pBuffer += tamanho_pessoa;
        }
    }
    pBuffer -= (tamanho_pessoa * n_pessoas) + sizeof(int);           //Seta ponteiro pro inicio 
}

void Listar()
{
    int n_pessoas = *((int*)pBuffer);

    printf("Numero de pessoas: %d\n",n_pessoas);
    pBuffer += sizeof(int);                         //Pula o n_pessoas

    for(int i=0;i<n_pessoas;i++)
    {
        printf("Nome: %s\n", (char*)pBuffer);       //Mostra nome
        pBuffer += (10 * sizeof(char));             //Pula o nome

        printf("Idade: %d\n", *(int*)pBuffer);      //Mostra idade
        pBuffer += sizeof(int);                     //Pula a idade

        printf("Telefone: %d\n", *(int*)pBuffer);   //Mostra telefone
        pBuffer += sizeof(int);                     //Pula o telefone
    }
    pBuffer -= (tamanho_pessoa * n_pessoas) + sizeof(int);           //Seta ponteiro pro inicio 
}

int main()
{
    pBuffer = malloc(sizeof(int));
    *((int*)pBuffer) = 0;
    int opcao;
    do
    {  
        opcao = Menu();
        switch (opcao)
        {
        case 1:
            Incluir();
            break;
        case 2:
            Apagar();
            break;
        case 3:
            Buscar();
            break;
        case 4:
            Listar();
            break;
        default:
            free(pBuffer);
            break;
        }
    }
    while (opcao!=5);
    return 0;
}