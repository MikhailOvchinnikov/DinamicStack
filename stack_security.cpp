#include "stack.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

//Hash coefficient
#define HASH 0.618033

//Canary's value
#define CANARY 0xFF


int HashFunc(void* inf, int size)
{
    char* point = (char*)inf;
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        result += (int)((size) * fmod(*(point++), HASH));
    }
    return result;
}



bool CheckHash(Stack* stack, int prev_hash_stack, int prev_hash_data)
{
    stack->hash = 0;
    stack->Data->hash = 0;
    bool ret = (HashFunc(stack->Data, sizeof(*(stack->Data))) == prev_hash_data) &&
        (HashFunc(stack, sizeof(*stack)) == prev_hash_stack);
    stack->hash = prev_hash_stack;
    stack->Data->hash = prev_hash_data;
    return ret;
}


bool CheckCanaries(Stack* stack)
{
    return ((stack->canary_left == CANARY) && (stack->canary_right == CANARY) && 
        (stack->Data->canary_left == CANARY) && (stack->Data->canary_right == CANARY));
}

bool CheckSizes(Stack* stack)
{
    return ((stack->Data->size <= stack->Data->capacity) && (stack->Data->size >= 0) && (stack->Data->capacity >= 0));
}


void Dump(const Stack* stack)
{
    if (stack == NULL)
    {
        return;
    } 
    printf("Stack<>[%p] \"%s\" at \"something place\" in programm at \"something file\"\n", stack, stack->name);
    printf("Size = %d\nCapacity = %d\n", stack->Data->size, stack->Data->capacity);
    printf("Data[%p]\n\t{\n", &stack->Data->data);
    for (int i = 0; i < stack->Data->capacity; i++)
    {
        if (i < stack->Data->size)
        {
            printf("\t\t[%d] %d\n", i, stack->Data->data[i]);
        }
        else
        {
            printf("\t\t[%d] (undefined value)\n", i);
        }
    }
    printf("\t}\n");
}


void AssertFunction(Stack* stack)
{

    if (stack == NULL)
    {
        printf("\n\n\t\tSTACK DOES NOT EXIST\n\n\n");
        assert(0);
    }
    if (!CheckCanaries(stack)) {
        printf("\n\n\t\tCANARY DIED\n\n\n");
        Dump(stack);
        assert(0);
    }
    if (!CheckSizes(stack)) {
        printf("\n\n\t\tBAD SIZE\n\n\n");
        Dump(stack);
        assert(0);
    }
    int prev_hash_stack = stack->hash;
    int prev_hash_data = stack->Data->hash;
    if (!CheckHash(stack, prev_hash_stack, prev_hash_data))
    {
        printf("\n\n\t\tHASH ERROR\n\n\n");
        Dump(stack);
        assert(0);
    }
}