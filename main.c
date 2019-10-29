#include <stdlib.h>
#include <stdio.h>
#include "Onegin.h"
#include "stack_hed.h"
#include "asem.h"
#include "CPU.h"
#include <math.h>


const int reg_num = 4;
const int stk_size = 15;


int main (int argc, char** argv) {

    if (argc < 4) {
        return INPUT_ERROR;
    }

    struct input data = acquire_input(argv);

    int size = count_file(data.name_in);

    char* bytecode = calloc(size, sizeof(char));

    FILE* asmm = fopen(data.name_in, data.type_in);


    fread(bytecode, sizeof(char), size, asmm);

    fclose(asmm);
    bytecode[size] = '\0';

    struct CPU processor = {};
    struct stack_t stk = {};

    init_stack(&stk, stk_size);

    init_CPU(&processor, &stk);

    for (int i = 0; i < size; ++i) {
        printf("%d ", bytecode[i]);
    }

    printf("\n");

    operate(&processor, bytecode);

    FILE* res = open_file(data.name_out, data.type_out);

    fprintf(res, "%d", stackPop(processor.stk));

    close_file(res);

    free(bytecode);


    return 0;
}