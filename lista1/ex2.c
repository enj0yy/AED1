#include<stdio.h>
#include<stdlib.h>
#include <string.h>

/*
====================
Menu
Menu do programa :).
====================
*/
int Menu()
{
    int opcao;
    do 
    {
        printf("-------------------------------------------------------\n");
        printf("1) Adicionar nome \n2) Remover nome \n3) Listar \n4) Sair\nEscolha uma opcao: ");
        scanf("%d",&opcao);
        printf("-------------------------------------------------------\n");
    } while(opcao < 1 || opcao > 4);
    return opcao;
}

/*
====================
AdicionarNome
Aumenta tamanho da string e adiciona novo nome :).
====================
*/
char * AdicionarNome(char * s)
{
    char nome[100];
    printf("Digite o nome: ");
    gets(nome);

    if(s == NULL)
    {
        s = (char*) malloc( (strlen(nome)+1) * sizeof(char));
        *s = '\0';
    }
    else
    {
        s = (char*) realloc(s, ( strlen(s) + strlen(nome) + 2 ) * sizeof(char) );
        strcat(s, "|");
    }

    strcat(s,nome);
    return s;
}

/*
====================
RemoverNome
Remove nome da string e diminui o tamanho :).
====================
*/
char * RemoverNome(char * s)
{
    char nome[100];
    char *token;
    int size_until_name_appear = 0;
    int new_size=0;

    char* temp = (char*)malloc( (strlen(s) + 1) * sizeof(char));
    strcpy(temp, s);
    
    printf("Digite o nome: ");
    gets(nome);

    token = strtok(temp, "|");
    while( token != NULL ) {
        size_until_name_appear += strlen(token)+1;
        if(strcmp(nome,token)==0)
        {
            for(int i = size_until_name_appear; (unsigned)i<(strlen(s));i++)
            {
                s[i-strlen(token)-1] = s[i];
            }
            new_size = (strlen(s) - strlen(token));
            s = (char*) realloc(s, new_size * sizeof(char));
            s[new_size-1] = '\0';
            break;
        }
        
        token = strtok(NULL, "|");
   }

    free(temp);
    return s;
}

/*
====================
Listar
Lista os nomes presentes na string :).
====================
*/
void Listar(char * s)
{
    char* temp = (char*)malloc( (strlen(s) + 1) * sizeof(char));
    strcpy(temp, s);
    char * token;

    token = strtok(temp,"|");
    while (token != NULL)
    {
        printf("%s\n",token);
        token = strtok(NULL,"|");
    }
    free(temp);
}

int main()
{   
    char *s;
    int opcao;
    s = NULL;

    do
    {  
        opcao = Menu();
        switch (opcao)
        {
        case 1:
            getchar();
            s = AdicionarNome(s);
            break;
        case 2:
            getchar();
            s = RemoverNome(s);
            break;
        case 3:
            Listar(s);
            break;
        default:
            free(s);
            break;
        }
        
    }
    while (opcao!=4);
    return 0;
}