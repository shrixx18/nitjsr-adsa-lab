#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack operations
char stack[MAX];
int top = -1;

void push(char c) {
    if (top >= MAX - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

char peek() {
    if (top == -1)
        return '\0';
    return stack[top];
}

// Precedence function
int prec(char c) {
    if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Infix to Postfix conversion
void infixToPostfix(char* exp) {
    int len = strlen(exp);
    char result[len + 1];
    int j = 0;

    for (int i = 0; i < len; i++) {
        char c = exp[i];

        if (isalnum(c)) {
            result[j++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && peek() != '(') {
                result[j++] = pop();
            }
            pop(); // Remove '('
        } else {
            while (top != -1 && prec(c) <= prec(peek())) {
                result[j++] = pop();
            }
            push(c);
        }
    }

    while (top != -1) {
        result[j++] = pop();
    }

    result[j] = '\0';
    printf("Postfix: %s\n", result);
}

// Main function
int main() {
    char exp[MAX];
    printf("Enter the expression: ");
    scanf("%s", exp);
    infixToPostfix(exp);
    return 0;
}