/*Develop a menu driven program to convert infix expression to prefix expression usingstack and evaluate
the prefix expression (Test for nested parenthesized expressions)
Note: Define Stack structure and implement the operations. Use different stacks forconversion and 
evaluation*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX 100

typedef struct Stack
{
    int digits[MAX];
    char operands[MAX];
    int top;
} Stack;

Stack *initStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        printf("Memroy allcoation failed.\n");
        exit(1);
    }
    stack->top = -1;
    return stack;
}

bool isEmpty(const Stack *stack)
{
    return stack->top == -1;
}

bool isFull(const Stack *stack)
{
    return stack->top == MAX - 1;
}

void pushDigits(Stack *stack, int digit)
{
    if (isFull(stack))
    {
        printf("Stack overflow.\n");
        return;
    }
    stack->digits[++(stack->top)] = digit;
}

void pushOperand(Stack *stack, char operand)
{
    if (isFull(stack))
    {
        printf("Stack overflow.\n");
        return;
    }
    stack->operands[++(stack->top)] = operand;
}

int popDigits(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow.\n");
        return -1;
    }
    return stack->digits[stack->top--];
}

char popOperands(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow.\n");
        return -1;
    }
    return stack->operands[stack->top--];
}

int peekDigits(const Stack *stack)
{
    return isEmpty(stack) ? -1 : stack->digits[stack->top];
}

char peekOperands(const Stack *stack)
{
    return isEmpty(stack) ? -1 : stack->operands[stack->top];
}

bool isOperand(const char c)
{
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isDigit(const char c)
{
    return (c >= '0' && c <= '9');
}

bool isOperator(const char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '$' || c == '^');
}

int precedence(const char c)
{
    if (c == '^' || c == '$')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

char *convert(const char *infix)
{
    int j = 0;
    int len = strlen(infix);

    Stack *stack = initStack();
    char *prefix = (char *)malloc(sizeof(char) * len);

    for (int i = len - 1; i >= 0; i--)
    {
        char token = infix[i];
        if (isOperand(token))
            prefix[j++] = token;
        else if (token == ')')
            pushOperand(stack, token);
        else if (token == '(')
        {
            while (!isEmpty(stack) && peekOperands(stack) != ')')
                prefix[j++] = popOperands(stack);

            if (!isEmpty(stack) && peekOperands(stack) == ')')
                popOperands(stack);
            else
            {
                printf("Invalid expression.\n");
                exit(1);
            }
        }
        else
        {
            while (!isEmpty(stack) && precedence(token) < precedence(peekOperands(stack)))
                prefix[j++] = popOperands(stack);

            pushOperand(stack, token);
        }
    }

    while (!isEmpty(stack))
        prefix[j++] = popOperands(stack);

    prefix[j] = '\0';

    for(int i = 0, j = strlen(prefix) - 1; i < j; i++, j--){
        char temp = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = temp;
    }

    return prefix;
}

int calculate(char operand, int operand1, int operand2)
{
    switch (operand)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    case '$':
    case '^':
        return pow(operand1, operand2);
    }
    return 0;
}

int evaluate(const char *postfix)
{
    Stack *stack = initStack();
    int len = strlen(postfix);

    for (int i = len - 1; i >= 0; i--)
    {
        char token = postfix[i];
        if (isDigit(token))
            pushDigits(stack, token - '0');
        else if (isOperator(token))
        {
            int operand1 = popDigits(stack);
            int operand2 = popDigits(stack);

            pushDigits(stack, calculate(token, operand1, operand2));
        }
    }
    return popDigits(stack);
}

int main()
{
    char infix[100];
    int choice;

    do
    {
        printf("\nMenu\n1. Convert\n2. Evaulate\n3. Exit\n");
        printf("Enter choice : ");
        scanf("%d", &choice);

        if (choice == 3)
        {
            printf("Exiting...\n");
            break;
        }

        printf("\nEnter infix expression : ");
        scanf("%s", infix);

        switch (choice)
        {
        case 1:
            printf("The converted infix expression to prefix is : %s\n", convert(infix));
            break;
        case 2:
            printf("The result of the expression is : %d\n", evaluate(convert(infix)));
            break;
        default:
            printf("Enter valid choice onlyyy..\n");
            break;
        }
    } while (choice != 3);
    return 0;
}