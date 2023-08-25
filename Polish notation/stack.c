#include "stack.h"

Stack* init(char c) {
    Stack* head = (Stack*)malloc(sizeof(Stack));
    head->next = NULL;
    head->symbol = c;
    return head;
}

Stack* push(Stack* root, char num) {
    Stack* new_elem = init(num);
    new_elem->next = root;
    return new_elem;
}

char pop(Stack** root) {
    char n = (*root)->symbol;
    Stack* tmp = (*root);
    (*root) = (*root)->next;
    free(tmp);
    return n;
}

char peek(Stack* root) { return root->symbol; }

void destroy(Stack* root) {
    if (root->next != NULL) {
        destroy(root->next);
    }
    free(root);
}
