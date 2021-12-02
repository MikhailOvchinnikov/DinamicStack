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


/// <summary>
/// Error codes
/// </summary>
enum ErrorCodes
{
    //stack_ptr pointer has a NULL pointer or not valid fields
    BADSTACK = 1,

    //canary data was corrupted
    CANARYDIED,

    //size of data has negative length or 0 length at the pop command
    BADSIZE,

    //different hash of something data
    BADHASH,

    //error memory allocation
    MEMORYERROR
};


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
    Data* data_struct = stack_ptr->data;

    int prev_h_stack = stack_ptr->hash;
    int prev_h_dat = data_struct->hash;
    int prev_h_arr = data_struct->hash_data;

    stack_ptr->hash = 0;
    data_struct->hash = 0;
    data_struct->hash_data = 0;
    bool f_ret = HashFunc(data_struct, sizeof(*(data_struct))) == prev_h_dat;
    bool s_ret = HashFunc(stack_ptr, sizeof(*stack_ptr)) == prev_h_stack;
    bool t_ret = HashFunc(data_struct->data, data_struct->capacity * sizeof(data_struct->data[0])) == prev_h_arr;

    stack_ptr->hash = prev_h_stack;
    data_struct->hash = prev_h_dat;
    data_struct->hash_data = prev_h_arr;

    return f_ret && s_ret && t_ret;
}

void HashClear(Stack* stack_ptr)
{
    Data* data_struct = stack_ptr->data;

    data_struct->hash = 0;
    data_struct->hash_data = 0;
    stack_ptr->hash = 0;
}


void HashCalc(Stack* stack_ptr)
{
    Data* data_struct = stack_ptr->data;

    stack_ptr->hash = HashFunc(stack_ptr, sizeof(*stack_ptr));
    data_struct->hash = HashFunc(data_struct, sizeof(*data_struct));
    data_struct->hash_data = HashFunc(data_struct->data, data_struct->capacity * sizeof(data_struct->data[0]));
}


bool CheckCanaries(Stack* stack_ptr)
{
    Data* data_struct = stack_ptr->data;

    bool f_ret = stack_ptr->canary_left == CANARY && stack_ptr->canary_right == CANARY;
    bool s_ret = data_struct->canary_left == CANARY && data_struct->canary_right == CANARY;
    bool t_ret = *data_struct->data_canary_left == CANARY && *data_struct->data_canary_right == CANARY;

    return f_ret && s_ret && t_ret;
}

bool CheckSizes(Stack* stack_ptr)
{
    Data* data_struct = stack_ptr->data;

    bool f_ret = data_struct->size <= data_struct->capacity;
    bool s_ret = data_struct->size >= 0;
    bool t_ret = data_struct->capacity >= 0;

    return f_ret && s_ret && t_ret;
}


void Dump(const Stack* stack_ptr, int line, const char* func, const char* file)
{
    if (stack_ptr == NULL)
    {
        return;
    } 

    Data* data_struct = stack_ptr->data;

    int cap = stack_ptr->data->capacity;
    int size = stack_ptr->data->size;

    FileLog("Stack<>[%p] \"%s\" in the \"%d\" line of the function \"%s\" in programm at \"%s\"\n", stack_ptr, stack_ptr->name, line, func, file);
    FileLog("Size = %d\nCapacity = %d\n", size, cap);
    FileLog("data[%p]\n\t{\n", &data_struct->data);

    for (int i = 0; i < cap; i++)
    {
        if (i < size)
        {
            FileLog("\t\t[%d] %d\n", i, data_struct->data[i]);
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
    Data* data_struct = stack_ptr->data;

    if (stack_ptr == NULL || data_struct == NULL || data_struct->memory == NULL)
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
