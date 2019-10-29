#include "asem.h"
#include "stack_hed.h"
#include "Onegin.h"
#include "CPU.h"
#include "math.h"


int init_CPU (struct CPU* proc, struct stack_t* stk) {

    proc->regax = 0;
    proc->regbx = 0;
    proc->regcx = 0;
    proc->regdx = 0;

    proc->stk = stk;


    return 0;
}

int find_command(int command, struct CPU* proc) {
    if (command == ax) {

        return proc->regax;

    } else if (command == bx) {

        return proc->regbx;

    } else if (command == cx) {

        return proc->regcx;

    } else if (command == dx) {

        return proc->regdx;

    } else return command;
}

int operate(struct CPU* proc, char* commands) {

    int current_comm = 0;
    struct stack_t temp_stk = {};
    init_stack(&temp_stk, 15);
    int acomp = 0;
    int bcomp = 0;

    int i = 0;
    int sqr_t = 0;

    while(commands[i] != '\0') {
        current_comm = commands[i];
        switch (current_comm) {
            case push:
                switch(commands[i + 1]) {
                    case ax:
                        stackPush(proc->stk, proc->regax);
                        i += 2;
                        break;
                    case bx:
                        stackPush(proc->stk, proc->regbx);
                        i += 2;
                        break;
                    case cx:
                        stackPush(proc->stk, proc->regcx);
                        i += 2;
                        break;
                    case dx:
                        stackPush(proc->stk, proc->regdx);
                        i += 2;
                        break;
                    default:
                        stackPush(proc->stk, commands[i + 1]);
                        i += 2;
                }
                break;
            case pop:
                switch(commands[i + 1]) {
                    case ax:
                        proc->regax = stackPop(proc->stk);
                        i += 2;
                        break;
                    case bx:
                        proc->regbx = stackPop(proc->stk);
                        i += 2;
                        break;
                    case cx:
                        proc->regcx = stackPop(proc->stk);
                        i += 2;
                        break;
                    case dx:
                        proc->regdx = stackPop(proc->stk);
                        i += 2;
                        break;
                    default:
                        stackPop(proc->stk);
                        ++i;
                }
                break;
            case in:
                switch(commands[i + 1]) {
                    case ax:
                        proc->regax = commands[i + 2];
                        i += 2;
                        break;
                    case bx:
                        proc->regbx = commands[i + 2];
                        i += 2;
                        break;
                    case cx:
                        proc->regcx = commands[i + 2];
                        i += 2;
                        break;
                    case dx:
                        proc->regdx = commands[i + 2];
                        i += 2;
                        break;
                    default:
                        stackPop(proc->stk);
                        ++i;
                }
                break;
            case mul:
                stackPush(proc->stk, stackPop(proc->stk) * stackPop(proc->stk));
                ++i;
                break;
            case dvd:
                stackPush(proc->stk, (stackPop(proc->stk)) / stackPop(proc->stk));
                ++i;
                break;
            case add:
                stackPush(proc->stk, stackPop(proc->stk) + stackPop(proc->stk));
                ++i;
                break;
            case sub:
                stackPush(proc->stk, (stackPop(proc->stk)) - stackPop(proc->stk));
                ++i;
            case end:
                ++i;
                return 0;
            case sqrtt:
                sqr_t = sqrt(stackPop(proc->stk));
                stackPush(proc->stk, sqr_t);
                ++i;
                break;
            case jmp:
                i = commands[i + 1] + 1;
                break;
            case je:
                acomp = find_command(commands[i + 1], proc);
                bcomp = find_command(commands[i + 2], proc);

                if (acomp== bcomp) {
                    i = commands[i + 3] + 1;
                    break;
                }

                i += 4;

                break;
            case jb:
                acomp = find_command(commands[i + 1], proc);
                bcomp = find_command(commands[i + 2], proc);

                if (acomp < bcomp) {
                    i = commands[i + 3] + 1;
                    break;
                }

                i += 4;

                break;
            case ja:
                acomp = find_command(commands[i + 1], proc);
                bcomp = find_command(commands[i + 2], proc);

                if (acomp > bcomp) {
                    i = commands[i + 3] + 1;
                    break;
                }

                i += 4;
                break;
            case jbe:
                acomp = find_command(commands[i + 1], proc);
                bcomp = find_command(commands[i + 2], proc);

                if (acomp <= bcomp) {
                    i = commands[i + 3] + 1;
                    break;
                }

                i += 4;
                break;
            case jae:
                acomp = find_command(commands[i + 1], proc);
                bcomp = find_command(commands[i + 2], proc);

                if (acomp >= bcomp) {
                    i = commands[i + 3] + 1;
                    break;
                }

                i += 4;
                break;

            case call:
                stackPush(&temp_stk, i + 2);
                i = commands[i + 1] + 1;
                break;
            case rett:
                i = stackPop(&temp_stk);
            default:
                break;
        }
    }
    stackClear(&temp_stk);

    return 0;
}
