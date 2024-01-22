#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node
{
    char element;
    struct Node *next;
} node;

typedef struct
{
    struct Node *Top;
    int Count;
} Stack;

#define top stack->Top
#define count stack->Count

node *createNode(char element)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        printf("Stack overflow.\n");
        exit(1);
    }
    newNode->element = element;
    newNode->next = NULL;
    return newNode;
}

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        printf("Memory allocaitn failad.\n");
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

void display(Stack *stack)
{
    if (!isEmpty(stack))
    {
        node *temp = top;
        while (temp)
        {
            node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
}

void push(Stack *stack, char element)
{
    node *newNode = createNode(element);
    if (isEmpty(stack))
    {
        top = newNode;
    }
    else
    {
        newNode->next = top;
        top = newNode;
    }
    count++;
}

char pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        // printf("Empty stack to pop. (Stack underflow.)\n");
        return -1;
    }
    node *toDelete = top;
    int element = toDelete->element;
    top = top->next;
    count--;
    free(toDelete);
    return element;
}

char stackTop(Stack *stack)
{
    if (isEmpty(stack))
    {
        // printf("Stack underflow, no elements at the stack top.\n");
        return -1;
    }
    return top->element;
}

int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else
        return 0;
}

bool isOperand(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char *infixToPostfix(const char *infix)
{
    int i = 0, j = 0;
    Stack *stack = createStack();
    char *postfix = (char *)malloc((strlen(infix) + 1) * sizeof(char));
    while (infix[i] != '\0')
    {
        char token = infix[i];
        if (isOperand(token))
        {
            postfix[j++] = token;
        }
        else if (token == '(')
            push(stack, token);
        else if (token == ')')
        {
            while (!isEmpty(stack) && stackTop(stack) != '(')
                postfix[j++] = pop(stack);
            if (!isEmpty(stack) && stackTop(stack) == '(')
                pop(stack);
        }
        else
        {
            while ((!isEmpty(stack) && precedence(token) <= precedence(stackTop(stack))) || (precedence(token) == precedence(stackTop(stack)) && stackTop(stack) == '^'))
                postfix[j++] = pop(stack);
            push(stack, token);
        }
        i++;
    }
    while (!isEmpty(stack))
        postfix[j++] = pop(stack);
    postfix[j] = '\0';
    return postfix;
}

char *infixToPrefix(const char *infix)
{
    char *reversedInfix = (char *)malloc((strlen(infix) + 1) * sizeof(char));
    int k = 0;
    for (int i = strlen(infix) - 1; i >= 0; i--)
        reversedInfix[k++] = infix[i];
    reversedInfix[k] = '\0';

    char *prefix = (char *)malloc((strlen(infix) + 1) * sizeof(char));
    int i = 0, j = 0;
    Stack *stack = createStack();
    while (reversedInfix[i] != '\0')
    {
        char token = reversedInfix[i];
        if (isOperand(token))
            prefix[j++] = token;
        else if (token == ')')
            push(stack, token);
        else if (token == '(')
        {
            while (!isEmpty(stack) && stackTop(stack) != ')')
                prefix[j++] = pop(stack);
            if (!isEmpty(stack) && stackTop(stack) == ')')
                pop(stack);
        }
        else
        {
            while (!isEmpty(stack) && precedence(token) < precedence(stackTop(stack)))
                prefix[j++] = pop(stack);
            push(stack, token);
        }
        i++;
    }
    while (!isEmpty(stack))
        prefix[j++] = pop(stack);

    prefix[j] = '\0';

    for (int i = 0, k = strlen(prefix) - 1; i < k; i++, k--)
    {
        char temp = prefix[i];
        prefix[i] = prefix[k];
        prefix[k] = temp;
    }

    return prefix;
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int postfixEvaluate(const char *postfix)
{
    int i = 0, operand1, operand2, result;
    Stack *stack = createStack();
    while (postfix[i] != '\0')
    {
        char token = postfix[i];
        if (isDigit(token))
            push(stack, token - '0');
        else if (isOperator(token))
        {
            operand1 = pop(stack);
            operand2 = pop(stack);
            switch (token)
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            case '^':
                result = operand1 ^ operand2;
                break;
            }
            push(stack, result);
        }
        i++;
    }
        return pop(stack);
}

int main()
{
    char infix[100];
    scanf("%s", infix);
    printf("%s, %s", infixToPostfix(infix), infixToPrefix(infix));
    printf("\n");
    printf("%d", postfixEvaluate(infixToPostfix(infix)));
    return 0;
}