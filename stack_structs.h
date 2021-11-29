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
    Data* data;

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
    float* data;

    //Common data
    float* memory;

    float* data_canary_left;
    float* data_canary_right;

    //Current size of stack with initialization elements
    int size;

    //Capacity of stack
    int capacity;

    //HashValue
    unsigned int hash;

    //HashValue
    unsigned int hash_data;

    //Right canary security
    unsigned int canary_right;

} Data;
