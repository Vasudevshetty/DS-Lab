#ifndef stack_int
#define stack_int

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct NodeInt
{
    int data;
    struct NodeInt *next;
} nodeInt;

typedef struct
{
    nodeInt *Top;
    int Count;
} StackInt;

#define topInt stackInt->Top
#define countInt stackInt->Count

nodeInt *createNodeInt(int data)
{
    nodeInt *newNode = (nodeInt *)malloc(sizeof(nodeInt));
    if (!newNode)
    {
        printf("Memory allcation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

StackInt *createStackInt()
{
    StackInt *stackInt = (StackInt *)malloc(sizeof(StackInt));
    if (!stackInt)
    {
        printf("Memmory allocaiton failed.\n");
        exit(1);
    }
    topInt = NULL;
    countInt = 0;
    return stackInt;
}

bool isEmptyInt(StackInt *stackInt)
{
    return !(topInt && countInt);
}

void pushInt(StackInt *stackInt, char data)
{
    nodeInt *newNode = createNodeInt(data);
    if (isEmptyInt(stackInt))
        topInt = newNode;
    else
    {
        newNode->next = topInt;
        topInt = newNode;
    }
    countInt++;
}

int popInt(StackInt *stackInt)
{
    if (isEmptyInt(stackInt))
    {
        printf("Stack under flow, popping failed.\n");
        return -1;
    }
    nodeInt *toDelete = topInt;
    int data = toDelete->data;
    topInt = toDelete->next;
    free(toDelete);
    countInt--;
    return data;
}

int peekInt(StackInt *stackInt)
{
    return isEmptyInt(stackInt) ? -1 : topInt->data;
}

void displayInt(StackInt *stackInt)
{
    if (isEmptyInt(stackInt))
    {
        printf("No elements to display.\n");
        return;
    }
    nodeInt *temp = topInt;
    printf("The elements of the stack are, \n");
    while (temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

#endif