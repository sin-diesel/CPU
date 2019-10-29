
#ifndef ASSEMBER_ASEM_H
#define ASSEMBER_ASEM_H


#include <stdio.h>
#include <stdlib.h>
#include "stack_hed.h"
#include "Onegin.h"



enum replacement {
    push = 101,
    pop = 102,
    in = 103,
    out = 104,
    dvd = 107,
    mul = 108,
    end = 109,
    INPUT_ERROR = -99,
    ax = 110,
    bx = 111,
    cx = 112,
    dx = 113,
    sqrtt = 114,
    add = 115,
    sub = 116,
    label = 117,
    jmp = 118,
    call = 119,
    rett = 120,
    je = 121,
    jb = 122,
    ja = 123,
    jbe = 124,
    jae = 125,
};



struct retval {
    int a;
    int b;
    int c;
    char* d;
    int jmp;
    int je;
    int jb;
    int ja;
    int jbe;
    int jae;
    int call;
};

struct lab {
    char* name;
    int command;
};


struct retval get_num(struct string strings);

int compile(struct string* strings, struct lab* labels, int str_size, char* out, int if_labels);

int assemble_conditional_jumps(char* p, struct retval* ret);

int seek_label(int str_size, struct lab* labels, char const *label);

#endif //ASSEMBER_ASEM_H
