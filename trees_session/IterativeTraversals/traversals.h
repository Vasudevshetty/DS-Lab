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
        if(temp){
            push(stack, temp);
            temp = temp->leftChild;
        }else{
            temp = pop(stack);
            printf("%d ", temp->data);
            temp = temp->rightChild;
        }
    }
    printf("\n");
}

void levelOrder(binaryTree* tree){
    TreeNode *temp = root;
    Queue *que = initQueue();
    enqueue(que, temp);
    while(!isEmptyQueue(que)){
        temp = dequeue(que);
        printf("%d ", temp->data);
        if(temp->leftChild)
            enqueue(que, temp->leftChild);
        if(temp->rightChild)
            enqueue(que, temp->rightChild);
    }
    printf("\n");
}