
#ifndef STACK_STRUCT_STACK_HED_H
#define STACK_STRUCT_STACK_HED_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define GYST_COUNTER 2
#define INIT_STACK_VALUE 3

#define POISON 666


//#define ASSERT_OK

#ifndef ASSERT_OK
#define ASSERT_OK
#else
#define ASSERT_OK if (StackOK(stk) != 0) { Dump(stk, StackOK(stk)); assert(!"Ok");}
#define POISON 666
#endif



typedef int elem_t;


enum errors {
    STACK_OVERFLOW = 20,
    STACK_UNDERFLOW = 30,
    INVALID_SIZE = 40,
    MEMORY_REALLOCATION_FAIL = 50,
    UNEXPECTED_STACK_ACCESS = 60
};


struct stack_t {
    const char* name;
    int size;
    int max_size;
    int min_size;
    elem_t HASH_VALUE;
    elem_t* data;
};


int Dump (struct stack_t* stk, int error);

int StackOK(struct stack_t* stk);

int init_stack(struct stack_t* stk, int size);

int moreMem(struct stack_t* stk);

int lessMem(struct stack_t* stk);

int stackPush(struct stack_t* stk, elem_t elem);

int stackClear(struct stack_t* stk);

elem_t stackPop(struct stack_t* stk);

int readCommand(struct stack_t* stk);






#endif
