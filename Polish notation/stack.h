#pragma once
#include <stdlib.h>

typedef struct stack {
    char symbol;
    struct stack* next;
} Stack;

Stack* init(char c);
Stack* push(Stack* root, char num);
char pop(Stack** root);
void destroy(Stack* root);
char peek(Stack* root);