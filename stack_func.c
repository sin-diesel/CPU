#include "Onegin.h"
#include "stack_hed.h"


const elem_t CAN_1 = 0xDED0BAD;
const elem_t CAN_2 = 0xEDA;


int Dump (struct stack_t* stk, int error) {
    assert(stk != NULL);

    FILE* dump_file = open_file("dump.txt", "a");

    fprintf(dump_file, "Stack_t : '%s'", stk->name);

//    if (strcmp(stk->name, "stk") == 0) {
//        fprintf(dump_file, "(ok)\n");
//    } else {
//        fprintf(dump_file, "(incorrect_name)\n)");
//    }
    fprintf(dump_file, "size = %d\n", stk->size);

    fprintf(dump_file, "max_size = %d\n", stk->max_size);

    fprintf(dump_file, "min_size = %d\n", stk->max_size);

    fprintf(dump_file, "Hash = %d\n", stk->HASH_VALUE);

    if (stk->data != NULL) {
        fprintf(dump_file, "canary1: 0x%x\n", *stk->data);
    }

    fprintf(dump_file, "returned value %d\n", error);

    fprintf(dump_file, "data [%d] = [%p] {\n", stk->size, stk);

    if (stk->data != NULL) {

        if (*(stk->data + sizeof(CAN_1)) == POISON) {

            fprintf(dump_file, "*[0] : %d\n (POISON?)", *(stk->data + sizeof(CAN_1)));

        } else {

            fprintf(dump_file, "*[0] : %d\n", *(stk->data + sizeof(CAN_1)));

        }


        if (*(stk->data + sizeof(CAN_1) + sizeof(elem_t)) == POISON) {

            fprintf(dump_file, "*[1] : %d\n (POISON?)", *(stk->data + sizeof(CAN_1) + sizeof(elem_t)));

        } else {

            fprintf(dump_file, "*[1] : %d\n", *(stk->data + sizeof(CAN_1) + sizeof(elem_t)));

        }

        if (*(stk->data + sizeof(CAN_1) + 2 * sizeof(elem_t)) == POISON) {

            fprintf(dump_file, "*[2] : %d\n (POISON?)", *(stk->data + sizeof(CAN_1) + 2 * sizeof(elem_t)));

        } else {

            fprintf(dump_file, "*[2] : %d\n", *(stk->data + sizeof(CAN_1) + 2 * sizeof(elem_t)));

        }
    }

    fprintf(dump_file, "}\n");

    fprintf(dump_file, "canary2: 0x%x\n", *(stk->data + sizeof(CAN_1) + sizeof(elem_t) * stk->max_size));

    fprintf(dump_file, "errno: %d", error);

    switch(error) {
        case STACK_OVERFLOW:
            fprintf(dump_file, "STACK_OVERFLOW");
            break;
        case STACK_UNDERFLOW:
            fprintf(dump_file, "STACK_UNDERFLOW");
            break;
        case INVALID_SIZE:
            fprintf(dump_file, "INVALID_SIZE");
            break;
        case MEMORY_REALLOCATION_FAIL:
            fprintf(dump_file, "MEMORY_REALLOCATION_FAIL");
            break;
        case UNEXPECTED_STACK_ACCESS:
            fprintf(dump_file, "UNEXPECTED_STACK_ACCESS");
            break;
        default:
            fprintf(dump_file, "UNEXPECTED_STACK_ACCESS");
    }

    fclose(dump_file);
    return error;
}

int StackOK(struct stack_t* stk) {
    assert(stk != NULL);
    int ret = 0;

    if (stk->min_size < 0) {
        ret = INVALID_SIZE;
    }



    if (stk->size < 0) {
        ret = INVALID_SIZE;
    }

    if (*(stk->data + sizeof(CAN_1) + sizeof(elem_t) * stk->max_size) != CAN_2) {
        ret = STACK_OVERFLOW;
    }

    if (*(stk->data) != CAN_1) {
        ret = STACK_UNDERFLOW;
    }

    if (stk->max_size < 0) {
        ret = INVALID_SIZE;
    }

    int sum = 0;

    for (int i = 0; i < stk->size; ++i) {
        sum += *(stk->data + sizeof(CAN_1) + sizeof(elem_t) * i) * i;
    }

    if (sum != stk->HASH_VALUE) {
        ret = UNEXPECTED_STACK_ACCESS;
    }

   // printf("\n%d", stk->HASH_VALUE);
    return ret;
}


int init_stack(struct stack_t* stk, int size) {
    assert(stk != NULL);

    stk->size = 0;
    stk->max_size = size;
    stk->min_size = 0;
    stk->HASH_VALUE = 0;

    if (size == 0) {
        stk->max_size = INIT_STACK_VALUE;//
    }
    if (stk->max_size < 0) {
        printf("INVALID_SIZE_INITIALIZATION, ABORTING");
        assert(!"OK");
    }

    stk->data = (elem_t*) calloc(size + sizeof(CAN_1) + sizeof(CAN_2) + sizeof(elem_t) * stk->max_size, sizeof(elem_t));
    *(stk->data) = CAN_1;
    *(stk->data + sizeof(CAN_1) + sizeof(elem_t) * size) = CAN_2;

    return 0;
}

int moreMem(struct stack_t* stk) {
    ASSERT_OK

    stk->data = (elem_t*) realloc(stk->data, sizeof(CAN_1) + sizeof(CAN_2) + (stk->max_size * GYST_COUNTER));

    if (stk->data == NULL) {
        Dump(stk, MEMORY_REALLOCATION_FAIL);
        exit(EXIT_FAILURE);
    }


    stk->min_size = stk->max_size / GYST_COUNTER;
    stk->max_size *= GYST_COUNTER;

    *(stk->data) = CAN_1;
    *(stk->data + sizeof(CAN_1) + sizeof(elem_t) * stk->max_size) = CAN_2;

    ASSERT_OK
    return 0;
}

int lessMem(struct stack_t* stk) {
    ASSERT_OK

    if (stk->size > 0) {

        stk->data = (elem_t*) realloc(stk->data, sizeof(CAN_1) + sizeof(CAN_2) + (stk->max_size / GYST_COUNTER));

        if (stk->data == NULL) {
            Dump(stk, MEMORY_REALLOCATION_FAIL);
            exit(EXIT_FAILURE);
        }
        stk->max_size /= GYST_COUNTER;
        stk->min_size /= GYST_COUNTER;

        *(stk->data) = CAN_1;
        *(stk->data + sizeof(CAN_1) + sizeof(elem_t) * stk->max_size) = CAN_2;
    }

    ASSERT_OK

    return 0;

}

int stackPush(struct stack_t* stk, elem_t elem) {
    ASSERT_OK

    if (stk->size >= stk->max_size) {
        moreMem(stk);
    }


    *(stk->data + sizeof(CAN_1) + sizeof(elem_t) * stk->size) = elem;

    stk->HASH_VALUE += elem * stk->size;

    //printf("[%d] %d\n", stk->size, *(stk->data + sizeof(CAN_1) + sizeof(elem_t ) * stk->size));


    stk->size++;

    ASSERT_OK

    return 0;
}

int stackClear(struct stack_t* stk) {
    ASSERT_OK

    for (int i = 0; i < stk->max_size; ++i) {
        *(stk->data + sizeof(CAN_1) + sizeof(elem_t) * i) = 666;
    }

    stk->size = 0;
    stk->max_size = 0;
    stk->min_size = 0;
    stk->HASH_VALUE = 0;

    return 0;
}

elem_t stackPop(struct stack_t* stk) {

    ASSERT_OK

    stk->size--;
    if (stk->size <= stk->min_size) {
        lessMem(stk);
    }

   // printf("[%d] %d\n", stk->size, *(stk->data + sizeof(CAN_1) + sizeof(elem_t) * stk->size));

    elem_t value = *(stk->data + sizeof(CAN_1) + sizeof(elem_t) * stk->size);

    stk->HASH_VALUE -= value * stk->size;

    *(stk->data + sizeof(CAN_1) + sizeof(elem_t) * stk->size) = 0;


    ASSERT_OK

    return value;

}

int readCommand(struct stack_t* stk) {
    char str[10] = {0};
    int num = 0;
    int ret = 0;
    scanf("%s", str);
    str[strlen(str)] = '\0';
    if (strcmp(str, "push") == 0) {
        scanf("%d", &num);
        ret = stackPush(stk, num);
    }
    if (strcmp(str, "pop") == 0) {
        ret = stackPop(stk);

    }
    return ret;
}
