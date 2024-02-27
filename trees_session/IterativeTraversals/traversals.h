/*Here are the iterative solutions of the all the traverasls and count nodes and hiehgt function on binary*/
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
    tree->Height = -1;
    tree->NodesCount = 0;
    return tree;
}

#define root tree->Root
#define height tree->Height
#define nodesCount tree->NodesCount

char *preOrderIterative(binaryTree *tree)
{
    TreeNode *temp = root;
    Stack *stack = initStack();
    char *traversalString = (char *)malloc(sizeof(char) * 100);
    int idx = 0;
    while (temp || !isEmpty(stack))
    {
        if (temp)
        {
            // printf("%d ", temp->data);
            // since we are taking out the string, if need the traversal please use recursive function in  utility classes.
            traversalString[idx++] = temp->data + '0';
            push(stack, temp);
            temp = temp->leftChild;
        }
        else
        {
            temp = pop(stack);
            temp = temp->rightChild;
        }
    }
    return traversalString;
}

char *inOrderIterative(binaryTree *tree)
{
    TreeNode *temp = root;
    Stack *stack = initStack();
    char *traversalString = (char *)malloc(sizeof(char) * 100);
    int idx = 0;
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
            traversalString[idx++] = temp->data + '0';
            // printf("%d ", temp->data);
            // since we are taking out the string, if need the traversal please use recursive function in  utility classes.
            temp = temp->rightChild;
        }
    }
    return traversalString;
}

char *postOrderIterative(binaryTree *tree)
{
    TreeNode *temp = tree->Root;
    Stack *stack1 = initStack();
    Stack *stack2 = initStack();
    char *traversalString = (char *)malloc(sizeof(char) * 100);
    int idx = 0;

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
    while (!isEmpty(stack2))
    {
        int data = pop(stack2)->data;
        // printf("%d ", data);
        // since we are taking out the string, if need the traversal please use recursive function in  utility classes.
        traversalString[idx++] = data + '0';
    }
    return traversalString;
}

char *levelOrderIterative(binaryTree *tree)
{
    TreeNode *temp = root;
    Queue *que = initQueue();
    char *traversalString = (char *)malloc(sizeof(char) * 100);
    int idx = 0;
    enqueue(que, temp);
    while (!isEmptyQueue(que))
    {
        temp = dequeue(que);
        traversalString[idx++] = temp->data + '0';
        // printf("%d ", temp->data);
        // since we are taking out the string, if need the traversal please use recursive function in  utility classes.
        if (temp->leftChild)
            enqueue(que, temp->leftChild);
        if (temp->rightChild)
            enqueue(que, temp->rightChild);
    }
    return traversalString;
}

void generate(const char *preOrderString, const char *inOrderString)
{

}