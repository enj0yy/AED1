/*
Você está subindo uma escada. São necessários n passos para chegar ao topo.
Cada vez você pode subir 1 ou 2 degraus. De quantas maneiras distintas você pode subir até o topo?
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

long double Fatorial(int n)
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

/*
Lógica:
Permutacao com repeticao!!!

1 ------------	qtd de loops/permutacoes: 0 = ceil(1/2)-1
1

2 ------------	qtd de loops/permutacoes: 0 = (2/2)-1
1 1 
2

3 ------------ 	qtd de loops/permutacoes: 1 = ceil(3/2)-1
1 1 1
(3-1)!/1!(3-2)!

4 ------------	qtd de loops/permutacoes: 1 = (4/2)-1
1 1 1
2 2
(4-1)!/1!(4-2)!

5 -------------	qtd de loops/permutacoes: 2 = ceil(5/2)-1
1 1 1 1 1
(5-1)!/1!(5-2)!
(5-2)!/2!(5-4)!

6 ------------	qtd de loops/permutacoes: 2 = (6/2)-1
1 1 1 1 1 1
2 2 2
(6-1)/1!(6-2)!
(6-2)/2!(6-4)!
*/
int QuantasManeirasComPermutacao(int n)
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

/*
Lógica:
0 -----------   base
1

1 ------------	base
1

2 ------------	passo
1+1 = 2

3 ------------ 	passo
2+1 = 3

4 ------------	passo
3+2 = 5
*/
int QuantasManeirasComRecursividade(int n)
{
    int maneiras;

    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        maneiras = QuantasManeirasComRecursividade(n-1) + QuantasManeirasComRecursividade(n-2);
    }
    
    return maneiras;
}

int QuantasManeirasSemRecursividade(int n)
{
    int maneiras;

    int a = 0;
    int b = 1;
    int soma;

    for(int i=1; i<=n; i++) 
    {
        soma = a + b; 
        maneiras = soma;
        a = b;    
        b = soma; 
    }
    
    return maneiras;
}

int main()
{
    int n;
    printf("Digite o n: ");
    scanf("%d",&n);

    printf("Maneiras (Permutacao): %d\n", QuantasManeirasComPermutacao(n));
    printf("Maneiras (Recursividade): %d\n", QuantasManeirasComRecursividade(n));
    printf("Maneiras (S/ Recursividade): %d\n", QuantasManeirasSemRecursividade(n));

    return 0;
}