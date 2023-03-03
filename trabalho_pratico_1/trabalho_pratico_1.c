#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int judgeCircle(char * moves)
{
    int posicao[2] = {0,0};

    for (int i=0; i<strlen(moves); i++)
    {
        if (moves[i] == 'R')
        {
            posicao[0] += 1;
        }
        if (moves[i] == 'L')
        {
            posicao[0] -= 1;
        }
        if (moves[i] == 'U')
        {
            posicao[1] += 1;
        }
        if (moves[i] == 'D')
        {
            posicao[1] -= 1;
        }
    }

    return (posicao[0] == 0 && posicao[1] == 0 ? 1 : 0 );
}

int main()
{
    int n;
    char * moves;
    
    printf("Digite o n de movimentos: ");
    scanf("%d",&n);

    moves = malloc( (n + 1) * sizeof(char) );
    printf("Digite a sequencia de movimentos: ");
    scanf("%s",moves);

    printf("O robo termina em (0,0)? %s\n", judgeCircle(moves) == 1 ? "Sim" : "Nao");

    return 0;
}