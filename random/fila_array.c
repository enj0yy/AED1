#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int * values;
    int first;
    int last;  
    int n_values;  
} MyQueue;

int myQueueEmpty(MyQueue* obj) {
  return obj->last == 0;
}

MyQueue* myQueueCreate() {
    MyQueue * obj;
    obj = (MyQueue*)malloc(sizeof(MyQueue));
    obj->values = NULL;
    obj->first=0;
    obj->last=0;
    obj->n_values=0;
    return obj;
}

void myQueuePush(MyQueue* obj, int x) {
    obj->n_values++;
    obj->values = (int*)realloc(obj->values,obj->n_values*sizeof(int));
    obj->values[obj->last]=x;
    obj->last++;  
}

int myQueuePop(MyQueue* obj) {
    int x=0;
    if(!myQueueEmpty(obj))
    {
        x=obj->values[obj->first];
        for(int i = obj->first; i<obj->n_values-1; i++)
        {
            obj->values[i]=obj->values[i+1];
        }
        obj->n_values--;
        obj->last--; 
        obj->values = (int*)realloc(obj->values,obj->n_values*sizeof(int));
    }
    return x;
}

int myQueuePeek(MyQueue* obj) {
    int peek;
    if(!myQueueEmpty(obj))
    {
        peek = obj->values[obj->first];     
    }
    return peek;
}

void myQueueFree(MyQueue* obj) {
    obj->values = (int*)realloc(obj->values,0);
    free(obj);
}

int main()
{
    MyQueue* obj = myQueueCreate();
    myQueuePush(obj, 1);
    myQueuePush(obj, 2);
 
    int peek = myQueuePeek(obj);
    int pop = myQueuePop(obj);
    int empty = myQueueEmpty(obj);

    printf("%d %d %d",peek,pop,empty);

    myQueueFree(obj);
}