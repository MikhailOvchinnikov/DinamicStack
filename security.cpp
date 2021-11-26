#include "stack.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include <stdarg.h>

//Hash coefficient
#define HASH 0.618033

//Canary's value
#define CANARY 0xFF


void FileLog(const char* format, ...)
{
    static FILE* log_file = fopen("stack_log.txt", "w");
    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);
}


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


bool CheckHash(Stack* stack_ptr)
{
    int prev_h_stack = stack_ptr->hash;
    int prev_h_dat = stack_ptr->data->hash;
    int prev_h_arr = stack_ptr->data->hash_data;

    stack_ptr->hash = 0;
    stack_ptr->data->hash = 0;
    stack_ptr->data->hash_data = 0;

    bool ret = (HashFunc(stack_ptr->data, sizeof(*(stack_ptr->data))) == prev_h_dat) &&
        (HashFunc(stack_ptr, sizeof(*stack_ptr)) == prev_h_stack) && 
        (HashFunc(stack_ptr->data->data, stack_ptr->data->capacity * sizeof(stack_ptr->data->data[0])) == prev_h_arr);

    stack_ptr->hash = prev_h_stack;
    stack_ptr->data->hash = prev_h_dat;
    stack_ptr->data->hash_data = prev_h_arr;
    return ret;
}

void HashClear(Stack* stack_ptr)
{
    stack_ptr->data->hash = 0;
    stack_ptr->data->hash_data = 0;
    stack_ptr->hash = 0;
}


void HashCalc(Stack* stack_ptr)
{
    stack_ptr->hash = HashFunc(stack_ptr, sizeof(*stack_ptr));
    stack_ptr->data->hash = HashFunc(stack_ptr->data, sizeof(*stack_ptr->data));
    stack_ptr->data->hash_data = HashFunc(stack_ptr->data->data, stack_ptr->data->capacity * sizeof(stack_ptr->data->data[0]));
}


bool CheckCanaries(Stack* stack_ptr)
{
    return ((stack_ptr->canary_left == CANARY) && (stack_ptr->canary_right == CANARY) && 
        (stack_ptr->data->canary_left == CANARY) && (stack_ptr->data->canary_right == CANARY) &&
        (*stack_ptr->data->data_canary_left == CANARY) && (*stack_ptr->data->data_canary_right == CANARY));
}

bool CheckSizes(Stack* stack_ptr)
{
    return ((stack_ptr->data->size <= stack_ptr->data->capacity) && (stack_ptr->data->size >= 0) && (stack_ptr->data->capacity >= 0));
}


void Dump(const Stack* stack_ptr, int line, const char* func, const char* file)
{
    if (stack_ptr == NULL)
    {
        return;
    } 
    FileLog("Stack<>[%p] \"%s\" in the \"%d\" line of the function \"%s\" in programm at \"%s\"\n", stack_ptr, stack_ptr->name, line, func, file);
    FileLog("Size = %d\nCapacity = %d\n", stack_ptr->data->size, stack_ptr->data->capacity);
    FileLog("data[%p]\n\t{\n", &stack_ptr->data->data);
    for (int i = 0; i < stack_ptr->data->capacity; i++)
    {
        if (i < stack_ptr->data->size)
        {
            FileLog("\t\t[%d] %d\n", i, stack_ptr->data->data[i]);
        }
        else
        {
            FileLog("\t\t[%d] (undefined value)\n", i);
        }
    }
    FileLog("\t}\n");
}


void StackExists(Stack* stack_ptr)
{
    if (stack_ptr == NULL || stack_ptr->data == NULL || stack_ptr->data->memory == NULL)
    {
        printf("\n\n\t\tBAD STACK\n\n\n");
        errno = ErrorCodes::BADSTACK;
    }
}


void AssertFunction(Stack* stack_ptr, int line,const char* func,const char* file)
{
    StackExists(stack_ptr);
    if(!errno)
    {
        if (!CheckCanaries(stack_ptr)) {
            FileLog("\n\n\t\tCANARY DIED\n\n\n");
            Dump(stack_ptr, line, func, file);
            errno = ErrorCodes::CANARYDIED;
        }
        else if (!CheckSizes(stack_ptr)) {
            FileLog("\n\n\t\tBAD SIZE\n\n\n");
            Dump(stack_ptr, line, func, file);
            errno = ErrorCodes::BADSIZE;
        }
        else if (!CheckHash(stack_ptr))
        {
            FileLog("\n\n\t\tHASH ERROR\n\n\n");
            Dump(stack_ptr, line, func, file);
            errno = ErrorCodes::BADHASH;
        }
    }
}
