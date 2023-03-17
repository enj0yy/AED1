#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _pessoa
{
    int idade;
    char nome[30];
} Pessoa;

typedef struct _pilha
{
    Pessoa * pessoas;
    Pessoa * topo;
    Pessoa * base;
    int n_pessoas;
} Pilha;


void Reset(Pilha * pilha)
{
    pilha->pessoas = NULL;
    pilha->topo = NULL;
    pilha->base = NULL;
    pilha->n_pessoas = 0;
}

int Empty(Pilha * pilha)
{
    return pilha->topo == NULL;
}

Pessoa NewPessoa(int idade, char * nome)
{
    Pessoa pessoa;
    pessoa.idade = idade;
    strcpy(pessoa.nome, nome);
    return pessoa;
}

int Push(Pilha * pilha, Pessoa pessoa)
{
    pilha->n_pessoas++;
    pilha->pessoas = realloc(pilha->pessoas, sizeof(Pessoa)*pilha->n_pessoas);

    if (pilha->pessoas == NULL)
    {
        printf("Erro na alocaçao!");
        exit(1);
    }

    pilha->pessoas[pilha->n_pessoas-1] = pessoa;
    pilha->topo = &pilha->pessoas[pilha->n_pessoas-1];
    pilha->base = &pilha->pessoas[0];

    return 1;
}

void Pop(Pilha * pilha, Pessoa * pessoa_pop)
{
    if (!Empty(pilha))
    {
        *pessoa_pop = *pilha->topo;
        pilha->n_pessoas--; 
        pilha->pessoas = realloc(pilha->pessoas,sizeof(Pessoa)*pilha->n_pessoas);   

        if (pilha->n_pessoas == 0)
        {
            Reset(pilha);
        }
        else
        {
            pilha->topo = &pilha->pessoas[pilha->n_pessoas-1]; 
            pilha->base = &pilha->pessoas[0]; 
        }
    }
}

void List(Pilha * pilha)
{
    Pessoa pessoa_pop;
    Pilha * pilha_copia;
    pilha_copia = (Pilha*)malloc(sizeof(Pilha));

    if (pilha_copia == NULL)
    {
        printf("Erro na alocaçao!");
        exit(1);
    }

    Reset(pilha_copia);

    while(!Empty(pilha))
    {
        Pop(pilha,&pessoa_pop);
        Push(pilha_copia,pessoa_pop);
        printf("Nome: %s Idade: %d \n",pessoa_pop.nome,pessoa_pop.idade);
    }

    while(!Empty(pilha_copia))
    {
        Pop(pilha_copia,&pessoa_pop);
        Push(pilha,pessoa_pop);
    }
    free(pilha_copia);
}

void DeleteByName(Pilha * pilha, char * nome)
{
    Pessoa pessoa_pop;
    Pilha * pilha_copia;
    pilha_copia = (Pilha*)malloc(sizeof(Pilha));

    if (pilha_copia == NULL)
    {
        printf("Erro na alocaçao!");
        exit(1);
    }

    Reset(pilha_copia);

    while(!Empty(pilha))
    {
        Pop(pilha,&pessoa_pop);
        Push(pilha_copia,pessoa_pop);
        if (strcmp(pessoa_pop.nome,nome) == 0) 
            break;
    }

    Pop(pilha_copia,&pessoa_pop);       //Tira da pilha copia o nome a ser deletado pra nao copiar de volta pra pilha original
    while(!Empty(pilha_copia))          //Copia a pilha copia para a pilha original sem o nome
    {      
        Pop(pilha_copia,&pessoa_pop);
        Push(pilha,pessoa_pop);
    }
    free(pilha_copia);
}

void Clear(Pilha * pilha)
{
    Pessoa pessoa_pop;
    while(!Empty(pilha))
    {
        Pop(pilha,&pessoa_pop);
    }
}

int main()
{
    Pilha * pilha;
    pilha = (Pilha*)malloc(sizeof(Pilha));

    if (pilha == NULL)
    {
        printf("Erro na alocaçao!");
        exit(1);
    }
    Reset(pilha);

    Push(pilha,NewPessoa(1,"nome 1"));
    Push(pilha,NewPessoa(2,"nome 2"));
    Push(pilha,NewPessoa(3,"nome 3"));

    printf("Pilha:\n");
    List(pilha);

    printf("Apagando o nome 2:\n");
    DeleteByName(pilha,"nome 2");
    List(pilha);

    printf("Limpando a pilha:\n");
    Clear(pilha);
    List(pilha);

    free(pilha);
    return 0;
}