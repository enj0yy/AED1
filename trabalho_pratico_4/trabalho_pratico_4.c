#include <stdio.h>
#include <stdlib.h>

void QuickSort(int vetor[], int esquerda, int direita)
{
    if (esquerda >= direita)
        return;

    int pivo = vetor[(esquerda + direita) / 2];
    int e = esquerda;
    int d = direita;
    int temp;

    while (e <= d)
    {
        while (vetor[e] < pivo)
            e++;

        while (vetor[d] > pivo)
            d--;

        if (e <= d)
        {
            temp = vetor[e];
            vetor[e] = vetor[d];
            vetor[d] = temp;
            e++;
            d--;
        }
    }

    QuickSort(vetor, esquerda, d);
    QuickSort(vetor, e, direita);
}

int * maxSubsequence(int * nums, int numsSize, int k, int * returnSize)
{
    int * soma;

    QuickSort(nums, 0, numsSize - 1);

    soma = malloc(sizeof(int) * k);

    for (int i = (numsSize - k); i < numsSize; i++)
        soma[(k + i) - numsSize] = nums[i];

    *returnSize = 1;
    return soma;
}

int main()
{
    int * soma;
    int returnSize;
    int tamanho;
    int k;

    // caso 1
    int nums[] = {2, 1, 3, 3};
    tamanho = 4;
    k = 2;
    soma = maxSubsequence(nums, tamanho, k, &returnSize);
    for (int j = 0; j < returnSize; j++)
        for (int i = 0; i < k; i++)
            printf("%d ", soma[i+j]);
    free(soma);

    printf("\n");

    // caso 2
    int nums2[] = {-1, -2, 3, 4};
    tamanho = 4;
    k = 3;
    soma = maxSubsequence(nums2, tamanho, k, &returnSize);
    for (int j = 0; j < returnSize; j++)
        for (int i = 0; i < k; i++)
            printf("%d ", soma[i+j]);
    free(soma);

    printf("\n");

    // caso 3
    int nums3[] = {3,4,3,3};
    tamanho = 4;
    k = 2;
    soma = maxSubsequence(nums3, tamanho, k, &returnSize);
    for (int j = 0; j < returnSize; j++)
        for (int i = 0; i < k; i++)
            printf("%d ", soma[i+j]);
    free(soma);

    printf("\n");
}