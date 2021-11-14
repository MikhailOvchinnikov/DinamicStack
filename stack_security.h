#pragma once

/// <summary>
/// Count hash of data
/// </summary>
/// <param name="inf">Pointer to data</param>
/// <param name="size">Size of one data element</param>
/// <returns>Unsigned int value of hash</returns>
int HashFunc(void* inf, int size);


/// <summary>
/// Check correct hash value of stack and array
/// </summary>
/// <param name="stack">Transmitted hash</param>
/// <returns>1 if hash value is correct, else 0</returns>
bool CheckHash(Stack* stack, int prev_hash_stack, int prev_hash_data);


/// <summary>
/// Check canaries' values
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <returns>1 if nothing has been changed, else 0</returns>
bool CheckCanaries(Stack* stack);


/// <summary>
/// Check stack sizes corectness
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <returns>1 if all sizes are right, else 0</returns>
bool CheckSizes(Stack* stack);


/// <summary>
/// Print information about stack: size, capacity, elements
/// </summary>
/// <param name="stack">Trnsmitted stack</param>
/// <returns>-1 if stack equal NULL, else 1</returns>
void Dump(const Stack* stack);


/// <summary>
/// Assert call depending on reason
/// </summary>
/// <param name="stack">Transmitted stack</param>
void AssertFunction(Stack* stack);