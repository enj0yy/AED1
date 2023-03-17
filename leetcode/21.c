#include <stdio.h>
#include <stdlib.h>

  struct ListNode {
      int val;
      struct ListNode *next;
  };

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    if (list1 == NULL || list2 == NULL)
    {
        return NULL;
    }
    
    struct ListNode * p_lista1_atual = list1->next;
    struct ListNode * p_lista1_anterior = list1;
    struct ListNode * p_lista2_atual = list2->next;
    struct ListNode * p_lista2_proximo = list2->next;

    int val;
    for(p_lista2_atual=list2->next;  p_lista2_atual!=NULL; p_lista2_atual=list2->next)
    {
        p_lista2_proximo = p_lista2_atual->next;
        val = p_lista2_atual->val;
        for(p_lista1_atual=list1->next;  p_lista1_atual!=NULL; p_lista1_atual=p_lista1_atual->next)
        {
            if(val<=p_lista1_atual->val)
            {
                p_lista1_anterior->next = p_lista2_atual;
                p_lista2_atual->next = p_lista1_atual;
                break;
            }
            if(val>=p_lista1_atual->val && p_lista1_atual->next == NULL)
            {
                p_lista1_atual->next = p_lista2_atual;
                p_lista2_atual->next = NULL;
                break;
            }
            p_lista1_anterior = p_lista1_atual;
        }
        
        list2->next = p_lista2_proximo;
    }

    return list1;
}

int main()
{
     //list1 = [1,2,3]
 //list2 = [/1/,3,4]

    struct ListNode * head1 = malloc(sizeof(struct ListNode));
    struct ListNode * n1 = malloc(sizeof(struct ListNode));
    struct ListNode * n2 = malloc(sizeof(struct ListNode));
    struct ListNode * n3 = malloc(sizeof(struct ListNode));
    head1->next = n1;

    n1->val = 1;
    n1->next = n2;
    n2->val = 2;
    n2->next = n3;
    n3->val = 4;
    n3->next = NULL;

    struct ListNode * head2 = malloc(sizeof(struct ListNode));
    struct ListNode * n_2_1 = malloc(sizeof(struct ListNode));
    struct ListNode * n_2_2 = malloc(sizeof(struct ListNode));
    struct ListNode * n_2_3 = malloc(sizeof(struct ListNode));
    head2->next = n_2_1;

    n_2_1->val = 1;
    n_2_1->next = n_2_2;
    n_2_2->val = 3;
    n_2_2->next = n_2_3;
    n_2_3->val = 4;
    n_2_3->next = NULL;

    struct ListNode * merged = malloc(sizeof(struct ListNode));

    merged = mergeTwoLists(head1,head2);

    for(struct ListNode * p = merged->next; p != NULL; p = p->next)
    {
        printf("Valor: %d\n",p->val);
    }
}