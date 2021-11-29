#include "stack.h"

#include <stdlib.h>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <errno.h>


//Defaul capacity of stack_ptr
#define INITIAL_CAPACITY 10

//Coefficient of resize stack_ptr's capacity
#define RESIZE_FACTOR 2

//Canary's value
#define CANARY 0xFF

//Def function for check stack_ptr adequate
#define StackOK(stack_ptr, line, func, file) AssertFunction(stack_ptr, line, func, file)

//Def function for check nullptr of stack_ptr
#define NotNULL(stack_ptr) StackExists(stack_ptr)


Stack* CreateStack(const char stack_name[])
{
    Stack* new_stack = (Stack*)calloc(1, sizeof(Stack));
    new_stack->data = (Data*)calloc(1, sizeof(Data));
    new_stack->data->memory = (float*)calloc(INITIAL_CAPACITY + 2, sizeof(float));

    NotNULL(new_stack);
    if (errno)
    {
        Clear(new_stack);
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, new_stack->name);
        return nullptr;
    }

    new_stack->data->capacity = INITIAL_CAPACITY;
    new_stack->data->size = 0;

    new_stack->canary_right = CANARY;
    new_stack->canary_left = CANARY;
    new_stack->data->canary_left = CANARY;
    new_stack->data->canary_right = CANARY;

    DataInitialization(new_stack);
    NameInititialization(new_stack->name, stack_name);
    HashClear(new_stack);
    HashCalc(new_stack);

    if (StackOK(new_stack, __LINE__, __FUNCTION__, __FILE__))
    {
        Clear(new_stack);
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, new_stack->name);
        return nullptr;
    }
    else
    {
        FileLog("Stack \"%s\"was created successfully\n", new_stack->name);
        return new_stack;
    }
}


int Push(Stack* stack_ptr, const float value)
{
    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return errno;
    }

    if (stack_ptr->data->size >= stack_ptr->data->capacity)
    {
        if (Resize(stack_ptr))
        {
            FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
            return errno;
        }
    }
    
    PushAction(stack_ptr, value);
    HashClear(stack_ptr);
    HashCalc(stack_ptr);

    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
    }
    else
    {
        FileLog("Command %s of the stack \"%s\" was successful, value %f\n", __FUNCTION__, stack_ptr->name, value);
    }
    return errno;
}


int Pop(Stack* stack_ptr, float* dst)
{
    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return errno;
    }
    if (stack_ptr->data->size == 0)
    {
        FileLog("Error pop, size of stack data is 0!\n");
        return errno = ErrorCodes::BADSIZE;
    }


    PopAction(stack_ptr, dst);
    HashClear(stack_ptr);
    HashCalc(stack_ptr);

    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
    }
    else
    {
        FileLog("Command %s of the stack \"%s\" was successful, value %f\n", __FUNCTION__, stack_ptr->name, *dst);
    }
    return errno;
}


int Size(Stack* stack_ptr, int* dst)
{
    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return errno;
    }
    *dst = stack_ptr->data->size;

    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
    }
    else
    {
        FileLog("Command %s of the stack \"%s\" was successful, value %d\n", __FUNCTION__, stack_ptr->name, *dst);
    }
    return errno;
}


int Capacity(Stack* stack_ptr, int* dst)
{
    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return errno;
    }

    *dst = stack_ptr->data->capacity;

    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
    }
    else
    {
        FileLog("Command %s of the stack \"%s\" was successful, value %d\n", __FUNCTION__, stack_ptr->name, *dst);
    }
    return errno;
}


int Resize(Stack* stack_ptr)
{
    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return errno;
    }

    stack_ptr->data->capacity *= RESIZE_FACTOR;
    stack_ptr->data->memory = (float*)realloc(stack_ptr->data->memory, (stack_ptr->data->capacity + 2) * sizeof(float));

    if(NotNULL(stack_ptr))
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return errno;
    }

    DataInitialization(stack_ptr);
    HashClear(stack_ptr);
    HashCalc(stack_ptr);

    if (StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__))
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
    }
    else
    {
        FileLog("Command %s of the stack \"%s\" was successful\n", __FUNCTION__, stack_ptr->name);
    }
    return errno;
}


void NameInititialization(char target_name[], const char get_name[])
{
    strncpy(target_name, get_name, ST_S);
}


void DataInitialization(Stack* stack_ptr)
{
    stack_ptr->data->data_canary_left = stack_ptr->data->memory;
    stack_ptr->data->data_canary_right = &stack_ptr->data->memory[stack_ptr->data->capacity + 1];
    stack_ptr->data->memory[0] = CANARY;
    stack_ptr->data->memory[stack_ptr->data->capacity + 1] = CANARY;
    stack_ptr->data->data = &stack_ptr->data->memory[1];
}


void PushAction(Stack* stack_ptr, float value)
{
    stack_ptr->data->data[stack_ptr->data->size] = value;
    stack_ptr->data->size++;
}


void PopAction(Stack* stack_ptr, float* dst)
{
    *dst = stack_ptr->data->data[stack_ptr->data->size - 1];
    stack_ptr->data->data[stack_ptr->data->size] = 0;
    stack_ptr->data->size--;
}


void Clear(Stack* stack_ptr)
{
    FileLog("Stack \"%s\" is deleting...\n", stack_ptr->name);
    free(stack_ptr->data->memory);
    free(stack_ptr->data);
    free(stack_ptr);
    FileLog("Deleting was successful");
}