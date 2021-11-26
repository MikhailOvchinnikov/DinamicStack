#pragma once

//Size of stack name
#define ST_S 32


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
int Push(Stack* stack, const int value);


/// <summary>
/// Reduce the stack size by decrementation of element's size
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="destin">Transmitted pointer to the variable</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int Pop(Stack* stack, int* destin);


/// <summary>
/// Return size of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="destin">Transmitted pointer to the variable</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int Size(Stack* stack, int* destin);


/// <summary>
/// Return capacity of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="destin">Transmitted pointer to the variable</param>
/// <returns>Return 0, if all actions were succesfull, else return error code</returns>
int Capacity(Stack* stack, int* destin);


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
/// Delete stack by free memory
/// </summary>
/// <param name="stack">Transmitted stack</param>
void Clear(Stack* stack);