#include <stdio.h>
#include "utility.h"

typedef struct
{
    TreeNode *Root;
    int Height, NodesCount;
} binaryTree;

binaryTree *initBinaryTree()
{
    binaryTree *tree = (binaryTree *)malloc(sizeof(binaryTree));
    if (!tree)
    {
        printf("Memory allcoation failed.\n");
        exit(1);
    }
    tree->Root = NULL;
    tree->Height = tree->NodesCount = 0;
    return tree;
}

#define root tree->Root
#define height tree->Height
#define nodesCount tree->NodesCount

void preOrder(binaryTree *tree)
{
    TreeNode *temp = root;
    Stack *stack = initStack();
    while (temp || !isEmpty(stack))
    {
        if (temp)
        {
            printf("%d ", temp->data);
            push(stack, temp);
            temp = temp->leftChild;
        }
        else
        {
            temp = pop(stack);
            temp = temp->rightChild;
        }
    }
    printf("\n");
}

void inOrder(binaryTree *tree)
{
    TreeNode *temp = root;
    Stack *stack = initStack();
    while (temp || !isEmpty(stack))
    {
        if (temp)
        {
            push(stack, temp);
            temp = temp->leftChild;
        }
        else
        {
            temp = pop(stack);
            printf("%d ", temp->data);
            temp = temp->rightChild;
        }
    }
    printf("\n");
}

void postOrder(binaryTree *tree)
{
    TreeNode *temp = tree->Root;
    Stack *stack1 = initStack();
    Stack *stack2 = initStack();

    push(stack1, temp);
    while (!isEmpty(stack1))
    {
        temp = pop(stack1);
        push(stack2, temp);
        if (temp->leftChild)
            push(stack1, temp->leftChild);
        if (temp->rightChild)
            push(stack1, temp->rightChild);
    }
    while(!isEmpty(stack2))
        printf("%d ", pop(stack2)->data);
    printf("\n");
}

void levelOrder(binaryTree *tree)
{
    TreeNode *temp = root;
    Queue *que = initQueue();
    enqueue(que, temp);
    while (!isEmptyQueue(que))
    {
        temp = dequeue(que);
        printf("%d ", temp->data);
        if (temp->leftChild)
            enqueue(que, temp->leftChild);
        if (temp->rightChild)
            enqueue(que, temp->rightChild);
    }
    printf("\n");
}