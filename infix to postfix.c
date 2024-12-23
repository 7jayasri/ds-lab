
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

char infix[MAX];
char postfix[MAX];
char stack[MAX];
int top = -1;

void push(char);
char pop(void);
int precedence(char);
void print(void);
int isempty(void);
void infixTopostfix(void);

int main() {
    printf("Enter the infix expression: ");
    gets(infix);
    infixTopostfix();
    print();
    return 0;
}

void push(char x) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    top++;
    stack[top] = x;
}

char pop() {
    char c;
    if (top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    c = stack[top];
    top--;
    return c;
}

int precedence(char x) {
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;
    else if (x == '^')
        return 3;
    else
        return 0;
}

void print() {
    int i;
    for (i = 0; postfix[i] != '\0'; i++)
        printf("%c", postfix[i]);
    printf("\n");
}

int isempty() {
    if (top == -1)
        return 1;
    else
        return 0;
}

void infixTopostfix() {
    int i, j = 0;
    char symbol, next;
    for (i = 0; infix[i] != '\0'; i++) {
        symbol = infix[i];
        if (symbol == '(')
            push(symbol);
        else if (symbol == ')') {
            while ((next = pop()) != '(')
                postfix[j++] = next;
        } else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^') {
            while (!isempty() && precedence(stack[top]) >= precedence(symbol)) {
                postfix[j++] = pop();
            }
            push(symbol);
        } else {
            postfix[j++] = symbol;
        }
    }
    while (!isempty()) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}
