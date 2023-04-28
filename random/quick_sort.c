// O(n^2) Se o pivo é aleatório tende a ser: O(n logn)
// Escolhe pivo, coloca todos numeros menores que ele pra esquerda, os maiores pra direita e posiciona ele por ultimo. Faz o mesmo com os numeros
// da direita e esquerda com recursao, quando o pivo ser o unico do vetor passado pra recursao ela para.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void QuickSort(int vetor[], int left, int right)
{
    if (left >= right)
        return;

    int pivo = vetor[(left + right) / 2];
    int l = left;
    int r = right;
    int temp;

    while(l<=r)
    {
        while(vetor[l] < pivo)
            l++;
        while(vetor[r] > pivo)
            r--;

        if (l <= r)
        {
            temp = vetor[l];
            vetor[l] = vetor[r];
            vetor[r] = temp;
            l++;
            r--;
        }
    }

    QuickSort(vetor,left,r);
    QuickSort(vetor,l,right);
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

    QuickSort(n,0,tamanho-1);

    for (int i=0; i<tamanho; i++)
    {
        printf("%d ", n[i]);
    } 
}