#pragma once
#include "stack.h"

char *polish_notation(char *string, int *error, int *exit);
int my_is_digit(char c);
int preority(char c);
char operators(const char *string, int *i_string);
void add_new_elem(char c, char *out_str, int *out_i);