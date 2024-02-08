#ifndef stack_int
#define stack_int

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

node *createNodeInt(int data)
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

Stack *createStackInt()
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

bool isEmptyInt(Stack *stack)
{
    return !(top && count);
}

void pushInt(Stack *stack, char data)
{
    node *newNode = createNodeInt(data);
    if (isEmptyInt(stack))
        top = newNode;
    else
    {
        newNode->next = top;
        top = newNode;
    }
    count++;
}

int popInt(Stack *stack)
{
    if (isEmptyInt(stack))
    {
        printf("Stack under flow, popping failed.\n");
        return -1;
    }
    node *toDelete = top;
    int data = toDelete->data;
    top = toDelete->next;
    free(toDelete);
    count--;
    return data;
}

int peekInt(Stack *stack)
{
    return isEmptyInt(stack) ? -1 : top->data;
}

void displayInt(Stack *stack)
{
    if (isEmptyInt(stack))
    {
        printf("No elements to display.\n");
        return;
    }
    node *temp = top;
    printf("The elements of the stack are, \n");
    while (temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

#endif