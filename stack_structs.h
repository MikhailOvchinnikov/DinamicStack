#pragma once

//Size of stack name
#define ST_S 32




/// <summary>
/// Struct with stack realization
/// </summary>
typedef struct Stack Stack;


/// <summary>
/// Struct with data realization
/// </summary>
typedef struct Data Data;


typedef struct Stack
{
    //Left canary security
    unsigned int canary_left;

    //Name of stack
    char name[ST_S] = {};

    //Struct for safe stack element
    Data* Data;

    //HashValue
    unsigned int hash;

    //Right canary security
    unsigned int canary_right;

} Stack;


typedef struct Data
{
    //Left canary security
    unsigned int canary_left;

    //Data of values
    int* data;

    //Common data
    int* memory;

    int* data_canary_left;
    int* data_canary_right;

    //Capacity of stack
    int size;

    //Current size of stack with initialization elements
    int capacity;

    //HashValue
    unsigned int hash;

    //Right canary security
    unsigned int canary_right;

} Data;




