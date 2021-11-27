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
    Data* data_ptr = stack_ptr->data;

    int prev_h_stack = stack_ptr->hash;
    int prev_h_dat = data_ptr->hash;
    int prev_h_arr = data_ptr->hash_data;

    stack_ptr->hash = 0;
    data_ptr->hash = 0;
    data_ptr->hash_data = 0;
    bool f_ret = HashFunc(data_ptr, sizeof(*(data_ptr))) == prev_h_dat;
    bool s_ret = HashFunc(stack_ptr, sizeof(*stack_ptr)) == prev_h_stack;
    bool t_ret = HashFunc(data_ptr->data, data_ptr->capacity * sizeof(data_ptr->data[0])) == prev_h_arr;

    stack_ptr->hash = prev_h_stack;
    data_ptr->hash = prev_h_dat;
    data_ptr->hash_data = prev_h_arr;

    return f_ret && s_ret && t_ret;
}

void HashClear(Stack* stack_ptr)
{
    stack_ptr->data->hash = 0;
    stack_ptr->data->hash_data = 0;
    stack_ptr->hash = 0;
}


void HashCalc(Stack* stack_ptr)
{
    Data* data_ptr = stack_ptr->data;
    stack_ptr->hash = HashFunc(stack_ptr, sizeof(*stack_ptr));
    data_ptr->hash = HashFunc(data_ptr, sizeof(*data_ptr));
    data_ptr->hash_data = HashFunc(data_ptr->data, data_ptr->capacity * sizeof(data_ptr->data[0]));
}


bool CheckCanaries(Stack* stack_ptr)
{
    Data* data_ptr = stack_ptr->data;
    bool f_ret = stack_ptr->canary_left == CANARY && stack_ptr->canary_right == CANARY;
    bool s_ret = data_ptr->canary_left == CANARY && data_ptr->canary_right == CANARY;
    bool t_ret = *data_ptr->data_canary_left == CANARY && *data_ptr->data_canary_right == CANARY;

    return f_ret && s_ret && t_ret;
}

bool CheckSizes(Stack* stack_ptr)
{
    Data* data_ptr = stack_ptr->data;
    bool f_ret = data_ptr->size <= data_ptr->capacity;
    bool s_ret = data_ptr->size >= 0;
    bool t_ret = data_ptr->capacity >= 0;

    return f_ret && s_ret && t_ret;
}


void Dump(const Stack* stack_ptr, int line, const char* func, const char* file)
{
    if (stack_ptr == NULL)
    {
        return;
    } 

    Data* data_ptr = stack_ptr->data;
    int cap = stack_ptr->data->capacity;
    int size = stack_ptr->data->size;

    FileLog("Stack<>[%p] \"%s\" in the \"%d\" line of the function \"%s\" in programm at \"%s\"\n", stack_ptr, stack_ptr->name, line, func, file);
    FileLog("Size = %d\nCapacity = %d\n", size, cap);
    FileLog("data[%p]\n\t{\n", &data_ptr->data);

    for (int i = 0; i < cap; i++)
    {
        if (i < size)
        {
            FileLog("\t\t[%d] %d\n", i, data_ptr->data[i]);
        }
        else
        {
            FileLog("\t\t[%d] (undefined value)\n", i);
        }
    }
    FileLog("\t}\n");
}


int StackExists(Stack* stack_ptr)
{
    Data* data_ptr = stack_ptr->data;
    if (stack_ptr == NULL || data_ptr == NULL || data_ptr->memory == NULL)
    {
        printf("\n\n\t\tBAD STACK\n\n\n");
        errno = ErrorCodes::BADSTACK;
        return -1;
    }
    return 0;
}


int AssertFunction(Stack* stack_ptr, int line,const char* func,const char* file)
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
    if (errno)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
