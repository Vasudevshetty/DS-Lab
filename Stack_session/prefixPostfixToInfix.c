// functions to convert prefix or postfix expression to infix.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 10

typedef struct Node
{
    char *data;
    struct Node *next;
} node;

typedef struct
{
    node *Top;
    int Count;
} Stack;

node *createNode(char *data)
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
    stack->Top = createNode('\0');
    stack->Count = 0;
    return stack;
}

#define top stack->Top->next
#define count stack->Count

bool isEmpty(Stack *stack)
{
    return !(top && count);
}

void push(Stack *stack, char *data)
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

char *pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack overflow, no elements to pop.\n");
        return NULL;
    }
    node *toDelete = top;
    char* data = toDelete->data;
    if (top->next)
        top = toDelete->next;
    else
        top = NULL;
    free(toDelete);
    count--;
    return data;
}

char *peek(Stack *stack)
{
    return isEmpty(stack) ? NULL : top->data;
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int main(){
    char v[20], va[29];
    scanf("%s %s", v, va);
    Stack *stack = initStack();
    push(stack, v);
    push(stack, va);
    node* temp = top;
    while (temp)
    {
        printf("%s ", temp->data);
        temp = temp->next;
    }
    printf("\n");
    return 0;
}