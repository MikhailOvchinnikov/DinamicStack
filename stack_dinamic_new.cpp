#include "stack.h"

#include <stdlib.h>
#include <cassert>
#include <stdio.h>

//Defaul capacity of stack
#define DEF_CAP 10

//Coefficient of resize stack's capacity
#define RESIZE_COEF 2

//Canary's value
#define CANARY 0xFF

//Def function for check stack adequate
#define StackOK(stack) { \
AssertFunction(stack);	 \
}



Stack* CreateStack(const char stack_name[])
{
    Stack* new_stack = (Stack*)malloc(sizeof(Stack));
    new_stack->Data = (Data*)malloc(sizeof(Data));
    new_stack->Data->capacity = DEF_CAP;
    new_stack->Data->size = 0;

    new_stack->Data->memory = (int*)calloc(new_stack->Data->capacity + 2, sizeof(int));
    new_stack->Data->data_canary_left = &(new_stack->Data->memory[0]);
    new_stack->Data->data_canary_right = &(new_stack->Data->memory[new_stack->Data->capacity + 1]);

    new_stack->Data->memory[0] = CANARY;
    new_stack->Data->memory[new_stack->Data->capacity + 1] = CANARY;
    new_stack->canary_right = CANARY;
    new_stack->canary_left = CANARY;
    new_stack->Data->canary_left = CANARY;
    new_stack->Data->canary_right = CANARY;

    new_stack->Data->data = &(new_stack->Data->memory[1]);
    NameInititialization(new_stack->name, stack_name);
    HashNull(&(new_stack->Data->hash), &new_stack->hash);
    new_stack->hash = HashFunc(new_stack, sizeof(*new_stack));
    new_stack->Data->hash = HashFunc(new_stack->Data, sizeof(*new_stack->Data));

    StackOK(new_stack);

    return new_stack;
}


void Push(Stack* stack, const int value)
{
    if (stack == NULL)
    {
        AssertFunction(stack);
    }

    StackOK(stack);

    if (stack->Data->size >= stack->Data->capacity)
    {
        Resize(stack);
    }
    stack->Data->data[stack->Data->size] = value;
    stack->Data->size++;
    HashNull(&(stack->Data->hash), &stack->hash);
    stack->hash = HashFunc(stack, sizeof(*stack));
    stack->Data->hash = HashFunc(stack->Data, sizeof(*stack->Data));

    StackOK(stack);
}


int Pop(Stack* stack)
{
    if (stack == NULL)
    {
        AssertFunction(stack);
    }
    if (stack->Data->size == 0)
    {
        printf("Error, size of stack is 0!\n");
        exit(4);
    }

    StackOK(stack);

    stack->Data->data[stack->Data->size] = 0;
    stack->Data->size--;
    HashNull(&(stack->Data->hash), &stack->hash);
    stack->hash = HashFunc(stack, sizeof(*stack));
    stack->Data->hash = HashFunc(stack->Data, sizeof(*stack->Data));

    StackOK(stack);

    return stack->Data->data[stack->Data->size];
}


int Size(Stack* stack)
{
    if (stack == NULL)
    {
        AssertFunction(stack);
    }

    StackOK(stack);

    return stack->Data->size;
}


int Capacity(Stack* stack)
{
    if (stack == NULL)
    {
        AssertFunction(stack);
    }

    StackOK(stack);

    return stack->Data->capacity;
}


void Resize(Stack* stack)
{
    StackOK(stack);

    stack->Data->capacity *= RESIZE_COEF;
    stack->Data->memory = (int*)realloc(stack->Data->memory, (stack->Data->capacity + 2) * sizeof(int));
    *stack->Data->data_canary_left = 0;
    *stack->Data->data_canary_right = 0;
    stack->Data->memory[0] = CANARY;
    stack->Data->memory[stack->Data->capacity + 1] = CANARY;
    stack->Data->data_canary_left = stack->Data->memory;
    stack->Data->data_canary_right = &(stack->Data->memory[stack->Data->capacity + 1]);
    stack->Data->data = &(stack->Data->memory[1]);

    HashNull(&(stack->Data->hash), &stack->hash);
    stack->hash = HashFunc(stack, sizeof(*stack));
    stack->Data->hash = HashFunc(stack->Data, sizeof(*stack->Data));

    StackOK(stack);
}


/*void Resize_to_size_stack(Stack* stack)
{
    if (stack == NULL)
    {
        AssertFunction(stack);
    }
    StackOK(stack);
    stack->Data->capacity = stack->Data->size;
    stack->Data->data = (int*)realloc(stack->Data->data, stack->Data->capacity * sizeof(int));
    //stack->hash = HashValueStack(stack);
    //stack->Data->hash = HashValueArray(stack->Data, stack->Data->capacity);
    StackOK(stack);
}*/


void NameInititialization(char target_name[], const char get_name[])
{
    size_t i = 0;
    for (i = 0; i < (strnlen(get_name, 31)); i++)
    {
        target_name[i] = get_name[i];
    }
    target_name[i] = '\0';
}

void HashNull(unsigned int* hash_data,unsigned int* hash_stack)
{
    *hash_data = 0;
    *hash_stack = 0;
}


void Clear(Stack** stack)
{
    free((*stack)->Data);
    free(*stack);
    *stack = NULL;
}