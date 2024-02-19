#ifndef stack_dynamic
#define stack_dynamic 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
    char data;
    struct Node *next;
} node;

typedef struct
{
    node *Top;
    int Count;
} Stack;

#define top stack->Top
#define count stack->Count

node *createNode(char data)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allcation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        printf("Memmory allocaiton failed.\n");
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

void push(Stack *stack, char data)
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

char pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack under flow, popping failed.\n");
        return -1;
    }
    node *toDelete = top;
    char data = toDelete->data;
    top = toDelete->next;
    free(toDelete);
    count--;
    return data;
}

char peek(Stack *stack)
{
    return isEmpty(stack) ? -1 : top->data;
}

void display(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("No elements to display.\n");
        return;
    }
    node *temp = top;
    printf("The elements of the stack are, \n");
    while (temp)
    {
        printf("%c ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

#endif