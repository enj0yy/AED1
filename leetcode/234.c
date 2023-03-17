#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};
 
typedef struct 
{
    int * valores;
    int topo;
    int base;
    int n_nodos;
} Pilha;

Pilha * Reset(Pilha * pilha)
{
    pilha = malloc(sizeof(Pilha));
    pilha->valores = NULL;
    pilha->topo = 0;
    pilha->base = 0;
    pilha->n_nodos = 0;
    return pilha;
}

void Push(Pilha * pilha, int valor)
{
    pilha->n_nodos++;
    pilha->valores = (int*)realloc(pilha->valores, pilha->n_nodos * sizeof(int));
    pilha->valores[pilha->topo] = valor;
    pilha->topo++;
}

void Pop(Pilha * pilha, int * valor)
{
    pilha->n_nodos--;
    pilha->topo--;
    *valor = pilha->valores[pilha->topo];
    pilha->valores = realloc(pilha->valores,sizeof(int)*pilha->n_nodos);
}

int ComparaPilhas(Pilha * pilha1, Pilha * pilha2)
{
    int valor1 = 0; 
    int valor2 = 0;
    while(pilha1->topo != 0)
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

int isPalindrome(struct ListNode* head){
    if (head->next == NULL)
    {
        return 1;
    }

    struct ListNode * p;
    int size = 0;
    int index = 0;
    int valor_pop;

    Pilha * pilha1 = NULL;
    Pilha * pilha2 = NULL;
    Pilha * pilha2_ajeitada = NULL;

    pilha1 = Reset(pilha1);
    pilha2 = Reset(pilha2);
    pilha2_ajeitada = Reset(pilha2_ajeitada);

    for (p=head->next; p!=NULL; p=p->next)
    size++;

    for (p=head->next; p!=NULL; p=p->next)
    {
        if (index<(size/2))
        {
            Push(pilha1,p->val);
        }
        else
        {
            Push(pilha2,p->val);
        }
        
        index++;
    }
    
    while(pilha2->topo!=0)
    {
        Pop(pilha2,&valor_pop);
        Push(pilha2_ajeitada,valor_pop);
    }

    if (size%2 == 1)
    Pop(pilha2_ajeitada,&valor_pop);

    return ComparaPilhas(pilha1,pilha2_ajeitada);
}

int main()
{
    struct ListNode * head = malloc(sizeof(struct ListNode));
    struct ListNode * n1 = malloc(sizeof(struct ListNode));
    struct ListNode * n2 = malloc(sizeof(struct ListNode));
    struct ListNode * n3 = malloc(sizeof(struct ListNode));

    head->next = n1;

    n1->val = 1;
    n1->next = n2;

    n2->val = 2;
    n2->next = n3;

    n3->val = 1;
    n3->next = NULL;

    printf("%d", isPalindrome(head));
}
