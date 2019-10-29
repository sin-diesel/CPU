
#ifndef HAMLET_HAMLET_H
#define HAMLET_HAMLET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

//#include "Onegin.c"

struct string {
    char* str;
    int length;
};

struct input {
    char* name_in;
    char* type_in;
    char* name_out;
    char* type_out;
};

void close_file(FILE* file);

void swap(struct string* a, struct string* b);

int is_letter(const char c);

int str_cmp1(struct string* s1, struct string* s2);

int str_cmp2(struct string* s1, struct string* s2);

void delete_spaces(FILE* file1, FILE* file2);


void copy_file(char* place, char* name);

void print_array(const char* arr, const int size);

struct input acquire_input(char** argv);

void print_array_infile(char* name, const struct string* p);

void quick_sort(struct string* p, int left, int right, int (*comp)(struct string* s1, struct string* s2));

int count_file(char* name);


void get_str(char* buffer, struct string* place);

int count_str(char* arr, const int size);

FILE* open_file (char* name, char* type);

char* create_buffer(char* name);

#endif //HAMLET_HAMLET_H
