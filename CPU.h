
#ifndef CPU_CPU_H
#define CPU_CPU_H

#include <stdio.h>
#include <stdlib.h>
#include "stack_hed.h"
#include "Onegin.h"
#include "asem.h"


struct CPU {

    int regax;
    int regbx;
    int regcx;
    int regdx;

    struct stack_t* stk;
};

int init_CPU (struct CPU* proc, struct stack_t* stk);

int operate(struct CPU* proc, char* commands);

int find_command(int command, struct CPU* proc);



#endif //CPU_CPU_H
