//2515. Shortest Distance to Target String in a Circular Array

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int closetTarget(char ** words, int wordsSize, char * target, int startIndex){
    int minimum_steps = -1;

    int steps = 0;
    int i = startIndex;
    do
    {
        if (strcmp(words[i],target) == 0) 
        {
            minimum_steps = steps;
            break;
        }
        steps++;
        i = (i + 1) % wordsSize;
    } while (i != startIndex); //pra frente

    i = startIndex;
    steps = 0;
    do
    {  
        if (strcmp(words[i],target)==0)
        {
            if (steps < minimum_steps)
                minimum_steps = steps;
            break;
        }
        steps++;
        i = (i - 1 + wordsSize) % wordsSize;
    } while (i != startIndex); //pra tras

    return minimum_steps;
}

int main()
{
    char * words[] = {"a","b","leetcode"};
    char target[] = "leetcode";
    int startIndex = 0;

    printf("%d", closetTarget(words,3,target,startIndex));
}