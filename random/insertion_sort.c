// O(n^2)
// Pega do segundo elemento ate o ultimo e acha onde inserir: compara com todos antes dele, se o elemento comparado for maior, 
// empurra ele uma posicao pra frente, no fim insere ele na posicao onde o while parou + 1.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InsertionSort(int vetor[], int tamanho)
{
    int temp, j;

    for(int i=1; i<tamanho; i++)
    {
        temp = vetor[i];    
        j = i-1;            
        while(j >= 0 && temp < vetor[j])
        {
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = temp;  
    }
}


int  main()
{              
    int n[10];
    int tamanho = 10;

    srand(time(NULL));
    for (int i=0; i<tamanho; i++)
    {
        n[i] = rand() % 10;
        printf("%d ", n[i]);
    }

    printf("\n");

    InsertionSort(n,tamanho);

    for (int i=0; i<tamanho; i++)
    {
        printf("%d ", n[i]);
    } 

    return 0;
}