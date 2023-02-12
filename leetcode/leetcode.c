//1528. Shuffle String - https://leetcode.com/problems/shuffle-string/

#include <stdio.h>
#include <stdlib.h>

/*
====================
RestoreString
Rearranja a string dada seguindo os indices fornecidos.
====================
*/
char * RestoreString(char * s, int* indices, int indicesSize){
    char *string_modificada;
    string_modificada = (char*)malloc( indicesSize * sizeof(char) + 1);
    for(int i=0; i<indicesSize; i++)
    {
        string_modificada[indices[i]]=s[i];
    }
    string_modificada[indicesSize] = '\0';
    return string_modificada;
}

int main()
{   
    char *string;
    int *indices;
    int n;

    printf("Digite o n: ");
    scanf("%d",&n);
    string = (char*)malloc( n * sizeof(char) + 1 );
    indices = (int*)malloc( n * sizeof(int) );

    printf("Digite a string: ");
    scanf("%s",string);
    
    printf("Digite os indices: \n");
    for(int i=0; i<n; i++)
    scanf("%d",&indices[i]);

    printf("String final: %s\n",RestoreString(string,indices,n));
    return 0;
}