#pragma once


/// <summary>
/// Create and initializate new stack
/// </summary>
/// <param name="stack_name">Transmitted name of stack</param>
/// <returns>Pointer to the initialized stack</returns>
Stack* CreateStack(const char stack_name[]);

/// <summary>
/// Push transmitted element on top of transmitted stack and return 0 or return error code, if stack was corrupted
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="value">The value to put on the stack</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int Push(Stack* stack, const float value);

/// <summary>
/// Reduce the stack size by decrementation of element's size
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="destin">Transmitted pointer to the variable</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int Pop(Stack* stack, float* destin);

/// <summary>
/// Return size of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="destin">Transmitted pointer to the variable</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int Size(Stack* stack, int* dst);

/// <summary>
/// Return capacity of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="destin">Transmitted pointer to the variable</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int Capacity(Stack* stack, int* dst);

/// <summary>
/// Increase stack capacity of stack or do nothing, if stack is empty
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int Resize(Stack* stack);

/// <summary>
/// Initialization stack's name by transmitted name
/// </summary>
/// <param name="target_name">Char array get transmitted name of Stack</param>
/// <param name="get_name">Transmitted name</param>
void NameInititialization(char target_name[], const char get_name[]);

/// <summary>
/// Initial pointers to data array, canaries and sizes 
/// </summary>
/// <param name="stack_ptr">Transmitted stack</param>
void DataInitialization(Stack* stack_ptr);

/// <summary>
/// Increase value of stack size and add new value
/// </summary>
/// <param name="stack_ptr">Transmitted stack</param>
/// <param name="value">Added value</param>
void PushAction(Stack* stack_ptr, float value);

/// <summary>
/// Decrease value of stack size, remove last element and set 0 value
/// </summary>
/// <param name="stack_ptr">Transmitted stack</param>
/// <param name="dst">Pointers for remove value</param>
void PopAction(Stack* stack_ptr, float* dst);

/// <summary>
/// Delete stack by free memory
/// </summary>
/// <param name="stack">Transmitted stack</param>
void Clear(Stack* stack);