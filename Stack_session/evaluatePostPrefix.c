#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef enum Notation
{
    prefix,
    postfix,
} Notation;

typedef struct Node
{
    int data;
    struct Node *next;
} node;

typedef struct
{
    node *Top;
    int Count;
} Stack;

#define top stack->Top
#define count stack->Count

node *createNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Stack *initStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        printf("Memory allcation failed.\n");
        exit(1);
    }
    top = NULL;
    count = 0;
    return stack;
}

bool isEmpty(Stack *stack)
{
    return !(top && count);
}

void push(Stack *stack, int data)
{
    node *newNode = createNode(data);
    if (isEmpty(stack))
        top = newNode;
    else
    {
        newNode->next = top;
        top = newNode;
    }
    count++;
}

int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack empty to pop.\n");
        return -1;
    }
    node *toDelete = top;
    int data = toDelete->data;
    top = toDelete->next;
    count--;
    return data;
}

int peek(Stack *stack)
{
    return isEmpty(stack) ? -1 : top->data;
}

int calculate(char operator, int operand1, int operand2)
{
    switch (operator)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    }
    return -1;
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int evualate(const char *expression, Notation notation)
{
    Stack *stack = initStack();
    int i = 0, len = strlen(expression);
    while(i < len){
        char token = notation == prefix ? expression[len - i - 1] : expression[i];
        if(isalnum(token))
            push(stack, token - '0');
        else if(isOperator(token)){
            int operand1 = pop(stack);
            int operand2 = pop(stack);

            int result = notation == prefix ? calculate(token, operand1, operand2) : calculate(token, operand2, operand1);
            push(stack, result);
        }
        i++;
    }
    return pop(stack);
}

int main()
{
    char s[10], su[10];
    scanf("%s", s);
    printf("%d\n", evualate(s, prefix));
    scanf("%s", su);
    printf("%d\n", evualate(su, postfix));
    return 0;
}