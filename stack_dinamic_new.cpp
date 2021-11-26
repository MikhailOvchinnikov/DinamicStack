#include "stack.h"

#include <stdlib.h>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <errno.h>


//Defaul capacity of stack_ptr
#define DEF_CAP 10

//Coefficient of resize stack_ptr's capacity
#define RESIZE_COEF 2

//Canary's value
#define CANARY 0xFF

//Def function for check stack_ptr adequate
#define StackOK(stack_ptr, line, func, file) AssertFunction(stack_ptr, line, func, file)

#define NotNULL(stack_ptr) StackExists(stack_ptr)


Stack* CreateStack(const char stack_name[])
{
    Stack* new_stack = (Stack*)calloc(1, sizeof(Stack));
    new_stack->data = (Data*)calloc(1, sizeof(Data));
    new_stack->data->memory = (int*)calloc(DEF_CAP + 2, sizeof(int));

    NotNULL(new_stack);
    if (errno)
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, new_stack->name);
        return nullptr;
    }

    new_stack->data->capacity = DEF_CAP;
    new_stack->data->size = 0;

    new_stack->data->data_canary_left = &(new_stack->data->memory[0]);
    new_stack->data->data_canary_right = &(new_stack->data->memory[new_stack->data->capacity + 1]);

    new_stack->data->memory[0] = CANARY;
    new_stack->data->memory[new_stack->data->capacity + 1] = CANARY;
    new_stack->canary_right = CANARY;
    new_stack->canary_left = CANARY;
    new_stack->data->canary_left = CANARY;
    new_stack->data->canary_right = CANARY;

    new_stack->data->data = &(new_stack->data->memory[1]);
    NameInititialization(new_stack->name, stack_name);
    HashClear(new_stack);
    HashCalc(new_stack);
    StackOK(new_stack, __LINE__, __FUNCTION__, __FILE__);

    if (errno)
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, new_stack->name);
        return nullptr;
    }
    else
    {
        FileLog("Stack \"%s\"was created successfully\n", new_stack->name);
        return new_stack;
    }
}


int Push(Stack* stack_ptr, const int value)
{
    StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__);
    if (errno)
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
    stack_ptr->data->data[stack_ptr->data->size] = value;
    stack_ptr->data->size++;
    HashClear(stack_ptr);
    HashCalc(stack_ptr);

    StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__);
    if (errno)
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
    }
    else
    {

        FileLog("Command %s of the stack \"%s\" was successful, value %d\n", __FUNCTION__, stack_ptr->name, value);
    }
    return errno;
}


int Pop(Stack* stack_ptr, int* destin)
{
    if (stack_ptr->data->size == 0)
    {
        FileLog("Error pop, size of stack data is 0!\n");
        return errno = ErrorCodes::BADSIZE;
    }

    StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__);
    if (errno)
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return errno;
    }

    *destin = stack_ptr->data->data[stack_ptr->data->size - 1];
    stack_ptr->data->data[stack_ptr->data->size] = 0;
    stack_ptr->data->size--;

    HashClear(stack_ptr);
    HashCalc(stack_ptr);

    StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__);
    if (errno)
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
    }
    else
    {

        FileLog("Command %s of the stack \"%s\" was successful, value %d\n", __FUNCTION__, stack_ptr->name, *destin);
    }
    return errno;
}


int Size(Stack* stack_ptr, int* destin)
{
    StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__);

    if (errno)
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return errno;
    }
    *destin = stack_ptr->data->size;

    StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__);
    if (errno)
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
    }
    else
    {
        FileLog("Command %s of the stack \"%s\" was successful, value %d\n", __FUNCTION__, stack_ptr->name, stack_ptr->data->size);
    }
    return errno;
}


int Capacity(Stack* stack_ptr, int* destin)
{
    StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__);

    if (errno)
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return errno;
    }

    *destin = stack_ptr->data->capacity;

    StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__);
    if (errno)
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
    }
    else
    {
        FileLog("Command %s of the stack \"%s\" was successful, value %d\n", __FUNCTION__, stack_ptr->name, stack_ptr->data->size);
    }
    return errno;
}


int Resize(Stack* stack_ptr)
{
    StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__);

    if (errno)
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return errno;
    }

    stack_ptr->data->capacity *= RESIZE_COEF;
    stack_ptr->data->memory = (int*)realloc(stack_ptr->data->memory, (stack_ptr->data->capacity + 2) * sizeof(int));

    NotNULL(stack_ptr);

    if(errno)
    {
        FileLog("Error command %s of the stack \"%s\"\n", __FUNCTION__, stack_ptr->name);
        return errno;
    }

    stack_ptr->data->memory[0] = CANARY;
    stack_ptr->data->memory[stack_ptr->data->capacity + 1] = CANARY;
    stack_ptr->data->data_canary_left = &(stack_ptr->data->memory[0]);
    stack_ptr->data->data_canary_right = &(stack_ptr->data->memory[stack_ptr->data->capacity + 1]);
    stack_ptr->data->data = &(stack_ptr->data->memory[1]);

    HashClear(stack_ptr);
    HashCalc(stack_ptr);

    StackOK(stack_ptr, __LINE__, __FUNCTION__, __FILE__);
    if (errno)
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
    size_t i = 0;
    for (i = 0; i < (strnlen(get_name, 31)); i++)
    {
        target_name[i] = get_name[i];
    }
    target_name[i] = '\0';
}


void Clear(Stack* stack_ptr)
{
    FileLog("Stack \"%s\" is deleting...\n", stack_ptr->name);
    free(stack_ptr->data->memory);
    free(stack_ptr->data);
    free(stack_ptr);
    FileLog("Deleting was successful");
}