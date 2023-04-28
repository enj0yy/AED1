// O(n^2)
// Pega do primeiro elemento ate o penultimo, acha o menor numero dele pra frente e troca de lugar com ele.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void SelectionSort(int vetor[], int tamanho)
{
    int menor_id, temp;

    for (int i=0; i<tamanho-1; i++)
    {
        menor_id = i;
        for (int j=i+1; j<tamanho; j++)
        {
            if (vetor[j] < vetor[menor_id])
                menor_id = j;
        }
        temp = vetor[i];
        vetor[i] = vetor[menor_id];
        vetor[menor_id] = temp;
    }
}


int main()
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

    SelectionSort(n,tamanho);

    for (int i=0; i<tamanho; i++)
    {
        printf("%d ", n[i]);
    } 
}