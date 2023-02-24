/*
Você está subindo uma escada. São necessários n passos para chegar ao topo.
Cada vez você pode subir 1 ou 2 degraus. De quantas maneiras distintas você pode subir até o topo?
*/

/*
Lógica:
Permutacao com repeticao!!!

1 ------------	qtd de loops/permutacoes: 0 = ceil(1/2)-1

2 ------------	qtd de loops/permutacoes: 0 = (2/2)-1

3 ------------ 	qtd de loops/permutacoes: 1 = ceil(3/2)-1
(3-1)!/1!(3-2)!

4 ------------	qtd de loops/permutacoes: 1 = (4/2)-1
(4-1)!/1!(4-2)!

5 -------------	qtd de loops/permutacoes: 2 = ceil(5/2)-1
(5-1)!/1!(5-2)!
(5-2)!/2!(5-4)!

6 ------------	qtd de loops/permutacoes: 2 = (6/2)-1
(6-1)/1!(6-2)!
(6-2)/2!(6-4)!
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int Fatorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * Fatorial(n-1);
    }
}

int QuantasManeiras(int n)
{
    int maneiras = 1;
    float qtd_permutacoes;

    if (n%2 == 0)
    {
        maneiras++;
    }

    qtd_permutacoes = ceil((float)n/2) - 1;

    for (int i=1; i<=qtd_permutacoes; i++)
    {
        maneiras += Fatorial(n-i) / (Fatorial(i)*Fatorial(n-i*2));
    }

    return maneiras;
}

int main()
{
    int n;
    printf("Digite o n: ");
    scanf("%d",&n);

    printf("Maneiras: %d", QuantasManeiras(n));
    return 0;
}