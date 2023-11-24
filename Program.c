#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct Stack {
    int top;
    char items[MAX_SIZE];
};

void push(struct Stack *stack, char item);
char pop(struct Stack *stack);
int isOperator(char c);
int precedence(char c);
void infixToPostfix(char *infixExpression, char *postfixExpression);

int main() {
    char infixExpression[MAX_SIZE];
    char postfixExpression[MAX_SIZE];

    printf("Enter an infix expression: ");
    scanf("%s", infixExpression);

    infixToPostfix(infixExpression, postfixExpression);

    printf("Postfix expression: %s\n", postfixExpression);

    return 0;
}

void push(struct Stack *stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = item;
}

char pop(struct Stack *stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    }
    return 0;  
}

void infixToPostfix(char *infixExpression, char *postfixExpression) {
    struct Stack stack;
    stack.top = -1; 

    int i, j;
    char ch;

    for (i = 0, j = 0; infixExpression[i] != '\0'; i++) {
        ch = infixExpression[i];

        if ((ch >= '0' && ch <= '9')) {
            postfixExpression[j++] = ch;
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (stack.top != -1 && stack.items[stack.top] != '(') {
                postfixExpression[j++] = pop(&stack);
            }
            if (stack.top == -1) {
                printf("Invalid expression - mismatched parentheses\n");
                exit(EXIT_FAILURE);
            }
            pop(&stack);  
        } else if (isOperator(ch)) {
            while (stack.top != -1 && precedence(ch) <= precedence(stack.items[stack.top])) {
                postfixExpression[j++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }    
    while (stack.top != -1) {
        if (stack.items[stack.top] == '(') {
            printf("Invalid expression - mismatched parentheses\n");
            exit(EXIT_FAILURE);
        }
        postfixExpression[j++] = pop(&stack);
    }

    postfixExpression[j] = '\0'; 
}
