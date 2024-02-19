#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode
{
    char Operator;
    struct TreeNode *operand1;
    struct TreeNode *operand2;
} treeNode;

treeNode *initTreeNode(char Operator)
{
    treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
    if (!newNode)
    {
        printf("Memory allocaiton failed.\n");
        exit(1);
    }
    newNode->Operator = Operator;
    newNode->operand1 = newNode->operand2 = NULL;
    return newNode;
}

typedef struct StackNode
{
    TreeNode *expression;
    StackNode *next;
} stackNode;

stackNode *initStackNode(TreeNode *expression)
{
    stackNode *newNode = (stackNode *)malloc(sizeof(stackNode));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->expression = expression;
    newNode->next = NULL;
    return newNode;
}
typedef struct
{
    stackNode *Top;
    int Count;
} Stack;

Stack *initStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    stack->Top = NULL;
    stack->Count = 0;
    return stack;
}

// define macros for easeier access.
#define top stack->Top
#define count stack->Count

bool isEmpty(Stack *stack)
{
    return !(top && count);
}

void push(Stack *stack, TreeNode *expression)
{
    stackNode *newNode = initStackNode(expression);
    if (isEmpty(stack))
        top = newNode;
    else
    {
        top->next = newNode;
        top = newNode;
    }
    count++;
}

TreeNode *pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow, cannot pop.\n");
        return NULL;
    }
    stackNode *toDelete = top;
    TreeNode *expression = toDelete->expression;
    top = top->next;
    free(toDelete->expression);
    free(toDelete);
    count--;
    return expression;
}

TreeNode* peek(Stack* stack){
    return isEmpty(stack) ? NULL : top->expression;
}

