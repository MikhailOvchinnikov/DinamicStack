#include "stack.h"

#include <stdio.h>
#include <stdlib.h>


int main()
{
    Stack* stack = CreateStack("Stack");
    int value = 0;
    int size = 0;
    Push(stack, 5);
    Push(stack, 13);
    Pop(stack, &value);
    Pop(stack, &value);
    Push(stack, 45);
    Push(stack, 23);
    Push(stack, 16);
    Push(stack, 100);
    Push(stack, 45);
    Push(stack, 23);
    Push(stack, 16);
    Push(stack, 100);
    Push(stack, 45);
    Push(stack, 23);
    Push(stack, 16);
    Push(stack, 100);

    Clear(stack);
    return 0;
}


