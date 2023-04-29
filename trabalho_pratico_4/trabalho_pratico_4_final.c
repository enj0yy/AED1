#include <stdio.h>
#include <stdlib.h>

typedef struct _elemento
{
    int num;
    int posicaoInicial;
} Elemento;

void QuickSortElement( Elemento vetor[], int esquerda, int direita )
{
    if ( esquerda >= direita )
        return;

    int pivo = vetor[(esquerda + direita) / 2].num;
    int e = esquerda;
    int d = direita;
    Elemento temp;

    while ( e <= d )
    {
        while ( vetor[e].num < pivo )
            e++;

        while ( vetor[d].num > pivo )
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

    QuickSortElement( vetor, esquerda, d );
    QuickSortElement( vetor, e, direita );
}

void QuickSortInt( int vetor[], int esquerda, int direita )
{
    if ( esquerda >= direita )
        return;

    int pivo = vetor[(esquerda + direita) / 2];
    int e = esquerda;
    int d = direita;
    int temp;

    while ( e <= d )
    {
        while ( vetor[e] < pivo )
            e++;

        while ( vetor[d] > pivo )
            d--;

        if ( e <= d )
        {
            temp = vetor[e];
            vetor[e] = vetor[d];
            vetor[d] = temp;
            e++;
            d--;
        }
    }

    QuickSortInt( vetor, esquerda, d );
    QuickSortInt( vetor, e, direita );
}

int * maxSubsequence( int * nums, int numsSize, int k, int * returnSize )
{ 
    Elemento numsTemp[numsSize];
    int indices[k];

    for ( int i = 0; i < numsSize; i++ )
    {
        numsTemp[i].num = nums[i];
        numsTemp[i].posicaoInicial = i;
    }

    QuickSortElement( numsTemp, 0, numsSize - 1 ); 

    for ( int i = (numsSize - k); i < numsSize; i++ )
        indices[(k + i) - numsSize] = numsTemp[i].posicaoInicial;

    QuickSortInt( indices,0,k-1 );

    int * soma;
    soma = malloc( sizeof(int) * k );
    for ( int i = 0; i < k; i++ )
        soma[i] = nums[indices[i]];

    *returnSize = k;
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
            printf("%d ", soma[j]);
    free(soma);

    printf("\n");

    // caso 2
    int nums2[] = {-1, -2, 3, 4};
    tamanho = 4;
    k = 3;
    soma = maxSubsequence(nums2, tamanho, k, &returnSize);
    for (int j = 0; j < returnSize; j++)
            printf("%d ", soma[j]);
    free(soma);

    printf("\n");

    // caso 3
    int nums3[] = {3,4,3,3};
    tamanho = 4;
    k = 2;
    soma = maxSubsequence(nums3, tamanho, k, &returnSize);
    for (int j = 0; j < returnSize; j++)
            printf("%d ", soma[j]);
    free(soma);

    printf("\n");

    // caso 4
    int nums4[] = {50,-75};
    tamanho = 2;
    k = 2;
    soma = maxSubsequence(nums4, tamanho, k, &returnSize);
    for (int j = 0; j < returnSize; j++)
            printf("%d ", soma[j]);
    free(soma);

    printf("\n");
}