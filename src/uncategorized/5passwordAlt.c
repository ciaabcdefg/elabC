#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char data;
    struct node* next;
} node;
typedef node stack;

stack* push(stack*, char);
stack* pop(stack*);

int main(void) {
    stack* s = NULL;
    
    char stop = 'x';
    char input[2048];

    fgets(input, 2048, stdin);

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == 'y') break;
        if (input[i] == 'x') {
            stop = 'y';
        }

        if (stop == 'x') {
            s = push(s, input[i]);
        }
        else if (stop == 'y' && input[i] == s->data) {
            s = pop(s);
        }
    }

    printf("%d", s == NULL);
    return 0;
}

stack* push(stack* s, char value) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) return NULL;

    newNode->data = value;
    newNode->next = s;

    return newNode;
}

stack* pop(stack* s) {
    if (s == NULL) return s;

    stack* temp = s;
    s = s->next;
    free(temp);

    return s;
}