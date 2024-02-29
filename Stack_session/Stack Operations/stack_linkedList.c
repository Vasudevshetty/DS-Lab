#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
    int element;
    struct Node *next;
} node;

typedef struct
{
    struct Node *Top;
    int Count;
} Stack;

#define top stack->Top->next
#define count stack->Count

node *createNode(int element)
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
}

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        printf("Memory allocaitn failad.\n");
        exit(1);
    }
    stack->Top = createNode(0);
    top = NULL;
    count = 0;
    return stack;
}

void display(const Stack *stack)
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
    free(stack->Top);
    free(stack);
}

bool isEmpty(const Stack *stack)
{
    return !(top && count);
}

void push(Stack *stack, int element)
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

int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Empty stack to pop. (Stack underflow.)\n");
        return -1;
    }
    node *toDelete = top;
    int element = toDelete->element;
    top = top->next;
    count--;
    free(toDelete);
    return element;
}

int stackTop(const Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow, no elements at the stack top.\n");
        return -1;
    }
    return top->element;
}

int main()
{
    Stack *stack = createStack();
    int element;
    int choice;
    do
    {
        printf("Menu.\n1. Push.\n2. Pop\n.3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the element : ");
            scanf("%d", &element);
            push(stack, element);
            display(stack);
            break;
        case 2:
            pop(stack);
            display(stack);
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
    } while (choice != 3);
    return 0;
}