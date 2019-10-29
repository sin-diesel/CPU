#include "asem.h"
#include "stack_hed.h"
#include "Onegin.h"
#include <strings.h>

#define NORET 666


int assemble_conditional_jumps(char* p, struct retval* ret) {
    char* reg = p;

    while (*p != ' ') {
        ++p;
    }
    *p = '\0';
    ++p;

    if (strcmp(reg, "ax") == 0) {
        ret->b = ax;
    } else if (strcmp(reg, "bx") == 0) {
        ret->b = bx;
    } else if (strcmp(reg, "cx") == 0) {
        ret->b = cx;
    } else if (strcmp(reg, "dx") == 0) {
        ret->b = dx;
    } else {
        ret->b = atoi(reg);
    }
    reg = p;

    while (*p != ' ') {
        ++p;
    }
    *p = '\0';
    ++p;

    if (strcmp(reg, "ax") == 0) {
        ret->c = ax;
    } else if (strcmp(reg, "bx") == 0) {
        ret->c = bx;
    } else if (strcmp(reg, "cx") == 0) {
        ret->c = cx;
    } else if (strcmp(reg, "dx") == 0) {
        ret->c = dx;
    } else {
        ret->c = atoi(reg);
    }

    ret->d = p;
    return 0;

}

struct retval get_num(struct string strings) {

    struct retval ret = {0, 0};
    char *p = strings.str;
    ret.a = NORET;
    ret.b = NORET;
    ret.c = NORET;
    ret.d = NULL;
    ret.jmp = -1;
    ret.call = -1;
    ret.je = -1;
    ret.jb = -1;
    ret.ja = -1;
    ret.jbe = -1;
    ret.jae = -1;


    if (*p == '\0') {
        ret.a = NORET;
        ret.b = NORET;
        ret.c = NORET;
        ret.d = NULL;
        ret.jmp = -1;
        ret.call = -1;
        ret.je = -1;
        ret.jb = -1;
        ret.ja = -1;
        ret.jbe = -1;
        ret.jae = -1;
        return ret;
    }

    if (*strings.str == ':') {
        strings.str += 1;
        ret.d = strings.str;
        return ret;
    }

    while (*p != ' ' && *p != '\0') {
        ++p;
    }

    if (*p != '\0') {
        *p = '\0';
        ++p;
    }


    if (strcmp(strings.str, "push") == 0) {
        ret.a = push;
        char *reg = p;

        if (strcmp(reg, "ax") == 0) {
            ret.b = ax;
        } else if (strcmp(reg, "bx") == 0) {
            ret.b = bx;
        } else if (strcmp(reg, "cx") == 0) {
            ret.b = cx;
        } else if (strcmp(reg, "dx") == 0) {
            ret.b = dx;
        } else {
            ret.b = atoi(p);
        }

        ret.c = NORET;
        return ret;

    } else if (strcmp(strings.str, "pop") == 0) {
        ret.a = pop;
        char *reg = p;


        if (strcmp(reg, "ax") == 0) {
            ret.b = ax;
        } else if (strcmp(reg, "bx") == 0) {
            ret.b = bx;
        } else if (strcmp(reg, "cx") == 0) {
            ret.b = cx;
        } else if (strcmp(reg, "dx") == 0) {
            ret.b = dx;
        } else {
            ret.b = atoi(p);
        }

        ret.c = NORET;
        return ret;

    } else if (strcmp(strings.str, "in") == 0) {
        ret.a = in;
        char *reg = p;
        while (*p != ' ') {
            ++p;
        }
        *p = '\0';
        ++p;

        if (strcmp(reg, "ax") == 0) {
            ret.b = ax;
        } else if (strcmp(reg, "bx") == 0) {
            ret.b = bx;
        } else if (strcmp(reg, "cx") == 0) {
            ret.b = cx;
        } else if (strcmp(reg, "dx") == 0) {
            ret.b = dx;
        }
        ret.c = atoi(p);
        return ret;

    } else if (strcmp(strings.str, "out") == 0) {
        ret.a = out;
        ret.b = NORET;
        ret.c = NORET;
        return ret;

    } else if (strcmp(strings.str, "sin") == 0) {
        ret.a = sin;
        ret.b = atoi(p);
        ret.c = NORET;
        return ret;

    } else if (strcmp(strings.str, "cos") == 0) {
        ret.a = cos;
        ret.b = atoi(p);
        ret.c = NORET;
        return ret;

    } else if (strcmp(strings.str, "dvd") == 0) {
        ret.a = dvd;
        ret.b = NORET;
        ret.c = NORET;
        return ret;

    } else if (strcmp(strings.str, "mul") == 0) {
        ret.a = mul;
        ret.b = NORET;
        ret.c = NORET;
        return ret;

    } else if (strcmp(strings.str, "end") == 0) {
        ret.a = end;
        ret.b = NORET;
        ret.c = NORET;
        return ret;

    } else if (strcmp(strings.str, "sqrt") == 0) {
        ret.a = sqrtt;
        ret.b = NORET;
        ret.c = NORET;
        return ret;

    } else if (strcmp(strings.str, "add") == 0) {
        ret.a = add;
        ret.b = NORET;
        ret.c = NORET;
        return ret;

    } else if (strcmp(strings.str, "sub") == 0) {
        ret.a = sub;
        ret.b = NORET;
        ret.c = NORET;
        return ret;

    } else if (strcmp(strings.str, "jmp") == 0) {
        ret.jmp = 0;
        ret.d = p;
        return ret;

    } else if (strcmp(strings.str, "call") == 0) {
        ret.call = 0;
        ret.d = p;
        return ret;
    } else if (strcmp(strings.str, "ret") == 0) {
        ret.a = rett;
        ret.b = NORET;
        ret.c = NORET;
        return ret;
    } else if (strcmp(strings.str, "je") == 0) {

        ret.je = 0;
        assemble_conditional_jumps(p, &ret);

    } else if (strcmp(strings.str, "jb") == 0) {
        ret.jb = 0;
        assemble_conditional_jumps(p, &ret);

    } else if (strcmp(strings.str, "ja") == 0) {
        ret.ja = 0;
        assemble_conditional_jumps(p, &ret);

    } else if (strcmp(strings.str, "jbe") == 0) {
        ret.jbe = 0;
        assemble_conditional_jumps(p, &ret);

    } else if (strcmp(strings.str, "jae") == 0) {
        ret.jae = 0;
        assemble_conditional_jumps(p, &ret);
    }



    return ret;
}

int compile(struct string* strings, struct lab* labels, int str_size, char* out, int if_labels) {

    int count = 0;

    int lab_count = 0;

    struct retval ret = {};

    for (int i = 0; i < str_size; ++i) {

        ret = get_num(strings[i]);


        if (ret.jmp == 0) {
            if (if_labels == 0) {
                out[count] = jmp;
            } else {
                out[count + 1] = seek_label(str_size, labels, ret.d);
            }
            count += 2;

        } else if (ret.je == 0) {
            if (if_labels == 0) {
                out[count] = je;
                out[count + 1] = ret.b;
                out[count + 2] = ret.c;
            } else {
                out[count + 3] = seek_label(str_size, labels, ret.d);
            }
            count += 4;

        } else if (ret.jb == 0) {
            if (if_labels == 0) {
                out[count] = jb;
                out[count + 1] = ret.b;
                out[count + 2] = ret.c;
            } else {
                out[count + 3] = seek_label(str_size, labels, ret.d);
            }
            count += 4;

        } else if (ret.ja == 0) {
            if (if_labels == 0) {
                out[count] = ja;
                out[count + 1] = ret.b;
                out[count + 2] = ret.c;
            } else {
                out[count + 3] = seek_label(str_size, labels, ret.d);
            }
            count += 4;

        } else if (ret.jbe == 0) {
            if (if_labels == 0) {
                out[count] = jbe;
                out[count + 1] = ret.b;
                out[count + 2] = ret.c;
            } else {
                out[count + 3] = seek_label(str_size, labels, ret.d);
            }
            count += 4;

        } else if (ret.jae == 0) {
            if (if_labels == 0) {
                out[count] = jae;
                out[count + 1] = ret.b;
                out[count + 2] = ret.c;
            } else {
                out[count + 3] = seek_label(str_size, labels, ret.d);
            }
            count += 4;

        } else if (ret.call == 0) {
            if (if_labels == 0) {
                out[count] = call;
            } else {
                out[count + 1] = seek_label(str_size, labels, ret.d);
            }
            count += 2;
        } else if (ret.a  == NORET && ret.b == NORET && ret.c == NORET && ret.d == NULL) {
            break;

        } else if (ret.d != NULL) {

            if (if_labels == 0) {
                labels[lab_count].name = ret.d;
                labels[lab_count].command = count;
                out[count] = label;
                ++lab_count;
            }
            ++count;

        } else if (ret.c != NORET) {

            if (if_labels == 0) {
                out[count] = ret.a;
                out[count + 1] = ret.b;
                out[count + 2] = ret.c;
            }
            count += 3;

        } else if (ret.b != NORET) {

            if (if_labels == 0) {
                out[count] = ret.a;
                out[count + 1] = ret.b;
            }
            count += 2;

        } else if (ret.a != NORET) {
            if (if_labels == 0) {
                out[count] = ret.a;
            }
            ++count;
        }
    }
    return count;
}


int seek_label(int str_size, struct lab* labels, char const *label) {

    for (int i = 0; i < str_size; ++i) {

        if (strcmp(labels[i].name, label) == 0) {
            return labels[i].command;
        }

    }
    return 0;
}