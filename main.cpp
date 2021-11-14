#include "stack.h"

#include <stdio.h>



int main()
{
    Stack* stack = CreateStack("Stack");
    Push(stack, 5);
    Push(stack, 13);
    printf("Size stack: %d\n", Size(stack));
    printf("Capacity size stack: %d\n", Capacity(stack));
    printf("Poped element: %d\n", Pop(stack));
    printf("Poped element: %d\n", Pop(stack));
    printf("Poped element: %d\n", Pop(stack));
    printf("Size stack: %d\n", Size(stack));
    printf("Capacity size stack: %d\n", Capacity(stack));
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

    printf("Size stack: %d\n", Size(stack));
    printf("Capacity size stack: %d\n", Capacity(stack));
    printf("Poped element: %d\n", Pop(stack));
    printf("Size stack: %d\n", Size(stack));
    printf("Capacity size stack: %d\n", Capacity(stack));

    Clear(&stack);


    /*printf("Size stack: %d\n", Size(stack));
    printf("Capacity size stack: %d\n", Capacity(stack));
    printf("Poped element: %d\n", Pop(stack));
    printf("Size stack: %d\n", Size(stack));
    printf("Capacity size stack: %d\n", Capacity(stack));


    Push(stack, 100);*/
    
    return 0;
}


