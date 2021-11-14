#pragma once
#include "stack_structs.h"
#include "stack_security.h"

#include <stdlib.h>
#include <string.h>

//Size of stack name
#define ST_S 32


/// <summary>
/// Create and initializate new stack
/// </summary>
/// <returns>Pointer to the initialized stack</returns>
Stack* CreateStack(const char stack_name[]);


/// <summary>
/// Push transmitted element on top of transmitted stack or do nothing, if stack == NULL
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="value">The value to put on the stack</param>
void Push(Stack* stack, const int value);


/// <summary>
/// Reduce the stack size by decrementation of element's size
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <returns>Deleted value or 0, if stack == NULL</returns>
int Pop(Stack* stack);


/// <summary>
/// Return size of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <returns>Element's size of stack, if stack == NULL return 666</returns>
int Size(Stack* stack);


/// <summary>
/// Return capacity of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <returns>Capacity of stack, if stack equal NULL return 666</returns>
int Capacity(Stack* stack);


/// <summary>
/// Increase stack capacity of stack or do nothing, if stack is empty
/// </summary>
/// <param name="stack">Transmitted stack</param>
void Resize(Stack* stack);


/// <summary>
/// Decrease stack capacity to element's size or do nothing, if stack == NULL
/// </summary>
/// <param name="stack">Transmitted stack</param>
void Resize_to_size_stack(Stack* stack);


/// <summary>
/// Initialization stack's name by transmitted name
/// </summary>
/// <param name="target_name">Char array get transmitted name of Stack</param>
/// <param name="get_name">Transmitted name</param>
void NameInititialization(char target_name[], const char get_name[]);

/// <summary>
/// Nullify hash of data
/// </summary>
/// <param name="hash_data">Array data</param>
/// <param name="hash_stack">Stack data</param>
void HashNull(unsigned int* hash_data,unsigned int* hash_stack);


/// <summary>
/// Delete stack by free memory
/// </summary>
/// <param name="stack">Transmitted stack</param>
void Clear(Stack** stack);