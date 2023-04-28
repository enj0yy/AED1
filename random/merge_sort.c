// O(n logn)
// Vai dividindo o vetor na metade com recursao ate ter só um elemento.
// Depois da merge nos 2 subvetores ordenados.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MergeSortedArrays(int vetor[], int inicio, int meio, int fim) {
    int e, d, v;
    int nEsquerda = meio - inicio + 1;
    int nDireita = fim - meio;
 
    int vetorEquerda[nEsquerda];
    int vetorDireita[nDireita];
 
    // Copiando para os vetores temporários
    for (e = 0; e < nEsquerda; e++)
        vetorEquerda[e] = vetor[inicio + e];
    for (d = 0; d < nDireita; d++)
        vetorDireita[d] = vetor[meio + 1 + d];
 
    e = 0;                                          // indice inicial do vetor da esquerda
    d = 0;                                          // indice inicial do vetor da direita
    v = inicio;                                     // indice inicial do vetor
    while (e < nEsquerda && d < nDireita) {
        if (vetorEquerda[e] <= vetorDireita[d]) {
            vetor[v] = vetorEquerda[e];
            e++;
        }
        else {
            vetor[v] = vetorDireita[d];
            d++;
        }
        v++;
    }
 
    // Se sobrar numeros no vetor da esquerda
    while (e < nEsquerda) {
        vetor[v] = vetorEquerda[e];
        e++;
        v++;
    }
 
    // Se sobrar numeros no vetor da direita
    while (d < nDireita) {
        vetor[v] = vetorDireita[d];
        d++;
        v++;
    }
}

void MergeSort(int vetor[], int inicio, int fim)
{
    if (inicio == fim)
        return;

    int meio = (inicio + fim) / 2;

    MergeSort(vetor,inicio,meio);
    MergeSort(vetor,meio+1,fim);
    MergeSortedArrays(vetor, inicio, meio, fim);
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

    MergeSort(n,0,tamanho-1);

    for (int i=0; i<tamanho; i++)
    {
        printf("%d ", n[i]);
    }

    return 0;
}