#include "polish_parser.h"

char *polish_notation(char *string, int *error, int *exit) {
    char *output_string = (char *)malloc(sizeof(char) * 1000);
    Stack *root = init(' ');
    int stack_count = 0, i_string = 0, i_output_string = 0;

    while (string[i_string] != '\0') {
        if (string[i_string] == 'q') {
            (*exit) = 0;
        }
        if ((*exit) == 0 || (*error) == 0) break;
        if (my_is_digit(string[i_string])) {
            int amount_quots = 0;
            while (my_is_digit(string[i_string]) || string[i_string] == '.') {
                if (string[i_string] == '.') amount_quots++;
                output_string[i_output_string++] = string[i_string++];
            }
            if (amount_quots > 1) {
                (*error) = 1;
            }
            output_string[i_output_string++] = ' ';
            i_string--;
        } else if (string[i_string] == '(') {
            root = push(root, string[i_string]);
            stack_count++;
        } else if (string[i_string] == ')') {
            while (peek(root) != '(' && stack_count > 0) {
                add_new_elem(pop(&root), output_string, &i_output_string);
                stack_count--;
            }
            pop(&root);
            stack_count--;
        } else if (string[i_string] == 'x') {
            add_new_elem('x', output_string, &i_output_string);
        } else if (string[i_string] != ' ') {
            char op;
            op = operators(string, &i_string);
            if (op != '?') {
                if (op == '-' && (i_output_string == 0 || (i_output_string > 1 && peek(root) == '('))) {
                    output_string[i_output_string++] = '~';
                } else {
                    while (stack_count > 0 && preority(peek(root)) >= preority(op)) {
                        add_new_elem(pop(&root), output_string, &i_output_string);
                        stack_count--;
                    }
                    root = push(root, op);
                    stack_count++;
                }
                i_string--;
            }
        }
        i_string++;
    }

    while (stack_count > 0 && peek(root) != '(') {
        add_new_elem(pop(&root), output_string, &i_output_string);
        stack_count--;
    }
    output_string[i_output_string++] = '\0';
    destroy(root);
    return output_string;
}

void add_new_elem(char c, char *out_str, int *out_i) {
    out_str[(*out_i)++] = c;
    out_str[(*out_i)++] = ' ';
}

int my_is_digit(char c) { return (c >= '0' && c <= '9'); }

int preority(char c) {
    int val = 0;
    if (c == '+' || c == '-')
        val = 1;
    else if (c == '*' || c == '/')
        val = 2;
    else if (c == 'S' || c == 'C' || c == 'T' || c == 'L' || c == 'G')
        val = 3;
    else if (c == 'Q')
        val = 4;
    return val;
}

char operators(const char *string, int *i_string) {
    int i = (*i_string);
    int l = 0;
    char operator[5] = "+-*/";
    char op = '?';
    for (int k = 0; k < 4; k++) {
        if (string[i] == operator[k]) {
            l = 1;
            op = string[i];
            (*i_string)++;
            break;
        }
    }
    if (l != 1 && string[i] != '\0' && string[i + 1] != '\0') {
        if (string[i] == 'l' && string[i + 1] == 'n') {
            op = 'L';
            (*i_string) += 2;
        } else if (string[i + 2] != '\0') {
            if (string[i] == 's' && string[i + 1] == 'i' && string[i + 2] == 'n') {
                op = 'S';
                (*i_string) += 3;
            } else if (string[i] == 'c' && string[i + 1] == 'o' && string[i + 2] == 's') {
                op = 'C';
                (*i_string) += 3;
            } else if (string[i] == 't' && string[i + 1] == 'a' && string[i + 2] == 'n') {
                op = 'T';
                (*i_string) += 3;
            } else if (string[i] == 'c' && string[i + 1] == 't' && string[i + 2] == 'g') {
                op = 'G';
                (*i_string) += 3;
            } else if (string[i] == 's' && string[i + 1] == 'q' && string[i + 2] == 'r' &&
                       string[i + 3] == 't') {
                op = 'Q';
                (*i_string) += 4;
            }
        }
    }
    return op;
}