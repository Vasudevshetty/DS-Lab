#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct treeNode
{
    char Operator;
    struct treeNode *operand1;
    struct treeNode *operand2;
} TreeNode;

TreeNode *initTreeNode(char Operator)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (!newNode)
    {
        printf("Memory allocaiton failed.\n");
        exit(1);
    }
    newNode->Operator = Operator;
    newNode->operand1 = newNode->operand2 = NULL;
    return newNode;
}

typedef struct stackNode
{
    TreeNode *expression;
    struct stackNode *next;
} StackNode;

StackNode *initStackNode(TreeNode *expression)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
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
    StackNode *Top;
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
    StackNode *newNode = initStackNode(expression);
    if (isEmpty(stack))
        top = newNode;
    else
    {
        newNode->next = top;
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
    StackNode *toDelete = top;
    TreeNode *expression = toDelete->expression;
    top = toDelete->next;
    free(toDelete);
    count--;
    return expression;
}

TreeNode *peek(Stack *stack)
{
    return isEmpty(stack) ? NULL : top->expression;
}

bool isOperand(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

TreeNode *constructExpressionTree(const char *postfix)
{
    int i = 0, len = strlen(postfix);
    Stack *stack = initStack();
    while (i < len)
    {
        char token = postfix[i];
        if (isOperand(token))
            push(stack, initTreeNode(token));
        else if (isOperator(token))
        {
            TreeNode *operand2 = pop(stack);
            TreeNode *operand1 = pop(stack);
            TreeNode *expression = initTreeNode(token);

            expression->operand2 = operand2;
            expression->operand1 = operand1;

            push(stack, expression);
        }
        i++;
    }
    return peek(stack);
}

void inOrder(TreeNode *root)
{
    if (!root)
        return;
    inOrder(root->operand1);
    printf("%c ", root->Operator);
    inOrder(root->operand2);
}