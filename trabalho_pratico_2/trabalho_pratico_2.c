#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode
{
    int val;
    struct ListNode * next;
};

typedef struct 
{
    int * valores;
    int topo;
    int base;
    int n_valores;
} Pilha;

int Empty(Pilha * pilha)
{
    return pilha->topo == 0;
}

void Clear(Pilha * pilha)
{
    free(pilha->valores);
    pilha->valores = NULL;
    pilha->topo = 0;
    pilha->base = 0;
    pilha->n_valores = 0;
}

Pilha * Reset()
{
    Pilha * pilha;
    pilha = (Pilha *)malloc(sizeof(Pilha));
    pilha->valores = NULL;
    pilha->topo = 0;
    pilha->base = 0;
    pilha->n_valores = 0;

    return pilha;
}

void Push(Pilha * pilha, int valor)
{
    pilha->n_valores++;
    pilha->valores = (int*)realloc(pilha->valores, pilha->n_valores * sizeof(int));
    pilha->valores[pilha->topo] = valor;
    pilha->topo++;
}

int Pop(Pilha * pilha, int * valor_pop)
{
    if (!Empty(pilha))
    {
        pilha->topo--;
        pilha->n_valores--;
        *valor_pop = pilha->valores[pilha->topo];
        pilha->valores = (int*)realloc(pilha->valores, pilha->n_valores * sizeof(int));
        return 1;
    }
    return 0;
}

int ComparaPilhas(Pilha * pilha1, Pilha * pilha2)
{
    int valor1;
    int valor2;
    while(!Empty(pilha1))       //as 2 pilhas sao do mesmo tamanho
    {
        Pop(pilha1,&valor1);
        Pop(pilha2,&valor2);
        if(valor1 != valor2)
        {
            return 0;
        }
    }
    return 1;
}

int isPalindrome(struct ListNode * head)
{
    int tamanho = 0;
    int index = 0;
    int valor;
    int e_palindromo;

    struct ListNode * p;

    Pilha * pilha1 = NULL;
    Pilha * pilha2 = NULL;
    Pilha * pilha2_arrumada = NULL;
    pilha1 = Reset();
    pilha2 = Reset();
    pilha2_arrumada = Reset();

    for(p = head->next; p!= NULL; p = p->next)  //saber o tamanho pra dividir em 2 pilhas
    {
        tamanho++;
    }

    for(p = head->next; p!= NULL; p = p->next)
    {
        if (index<(tamanho/2))
        {
            Push(pilha1,p->val);
        }
        else
        {
            Push(pilha2,p->val);
        }
        index++;
    }

    while(!Empty(pilha2))   //inverter a pilha 2 para poder comparar
    {
        Pop(pilha2,&valor);
        Push(pilha2_arrumada,valor);
    }

    if(tamanho%2 == 1)      //se o tamanho for impar nao compara o nodo do meio, entao tira ele da pilha 2
    {
        Pop(pilha2_arrumada,&valor);
    }
    
    e_palindromo = ComparaPilhas(pilha1,pilha2_arrumada); //compara as 2 pilhas topo == topo ate o final

    Clear(pilha1);
    free(pilha1);
    Clear(pilha2);
    free(pilha2);
    Clear(pilha2_arrumada);
    free(pilha2_arrumada);
    p = NULL;
    free(p);

    return e_palindromo;
}

int main()
{  
    struct ListNode * head = malloc(sizeof(struct ListNode));
    struct ListNode * n1 = malloc(sizeof(struct ListNode));
    struct ListNode * n2 = malloc(sizeof(struct ListNode));
    struct ListNode * n3 = malloc(sizeof(struct ListNode));
    struct ListNode * n4 = malloc(sizeof(struct ListNode));

    //Caso 1 cabeça = [1,2,2,1]
    head->next = n1;
    n1->val = 1;    n1->next = n2;
    n2->val = 2;    n2->next = n3;
    n3->val = 2;    n3->next = n4;
    n4->val = 1;    n4->next = NULL;
    printf("%s\n", isPalindrome(head) ? "E palindromo :D" : "Nao e palindromo D:");

    //Caso 2 cabeça = [1,2]
    head->next = n1;
    n1->val = 1;    n1->next = n2;
    n2->val = 2;    n2->next = NULL;
    printf("%s\n", isPalindrome(head) ? "E palindromo :D" : "Nao e palindromo D:");

    //Caso 3 cabeça = [1,2,1]
    head->next = n1;
    n1->val = 1;    n1->next = n2;
    n2->val = 2;    n2->next = n3;
    n3->val = 1;    n3->next = NULL;
    printf("%s\n", isPalindrome(head) ? "E palindromo :D" : "Nao e palindromo D:");

    free(head);
    free(n1);
    free(n2);
    free(n3);
    free(n4);

    return 0;
}