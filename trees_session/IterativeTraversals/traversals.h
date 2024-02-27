/*Here are the iterative solutions of the all the traverasls and count nodes and hiehgt function on binary*/
#include <stdio.h>
#include <string.h>
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

// function prototypes.

// traversal functions.
int *preOrderIterative(binaryTree *);
int *inOrderIterative(binaryTree *);
int *postOrderIterative(binaryTree *);
int *levelOrderIterative(binaryTree *);

// height counter.
int calculateHeight(TreeNode *);
int getHeight(binaryTree *);

// nodes counter.
int countNodes(TreeNode *);
int getNodesCount(binaryTree *);

// tree construction.
TreeNode *buildTree(const int *, const int *, int, int);
binaryTree *generateTree(const int *, const int *, int);

#define root tree->Root
#define height tree->Height
#define nodesCount tree->NodesCount

int *preOrderIterative(binaryTree *tree)
{
    TreeNode *temp = root;
    Stack *stack = initStack();
    int *traversal = (int *)malloc(sizeof(int) * getNodesCount(tree));
    int idx = 0;
    while (temp || !isEmpty(stack))
    {
        if (temp)
        {
            // printf("%d ", temp->data);
            // since we are taking out the string, if need the traversal please use recursive function in  utility classes.
            traversal[idx++] = temp->data;
            push(stack, temp);
            temp = temp->leftChild;
        }
        else
        {
            temp = pop(stack);
            temp = temp->rightChild;
        }
    }
    return traversal;
}

int *inOrderIterative(binaryTree *tree)
{
    TreeNode *temp = root;
    Stack *stack = initStack();
    int *traversal = (int *)malloc(sizeof(int) * getNodesCount(tree));
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
            traversal[idx++] = temp->data;
            // printf("%d ", temp->data);
            // since we are taking out the string, if need the traversal please use recursive function in  utility classes.
            temp = temp->rightChild;
        }
    }
    return traversal;
}

int *postOrderIterative(binaryTree *tree)
{
    TreeNode *temp = tree->Root;
    Stack *stack1 = initStack();
    Stack *stack2 = initStack();
    int *traversal = (int *)malloc(sizeof(int) * getNodesCount(tree));
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
        traversal[idx++] = data;
    }
    return traversal;
}

int *levelOrderIterative(binaryTree *tree)
{
    TreeNode *temp = root;
    Queue *que = initQueue();
    int *traversal = (int *)malloc(sizeof(int) * getNodesCount(tree));
    int idx = 0;
    enqueue(que, temp);
    while (!isEmptyQueue(que))
    {
        temp = dequeue(que);
        traversal[idx++] = temp->data;
        // printf("%d ", temp->data);
        // since we are taking out the string, if need the traversal please use recursive function in  utility classes.
        if (temp->leftChild)
            enqueue(que, temp->leftChild);
        if (temp->rightChild)
            enqueue(que, temp->rightChild);
    }
    return traversal;
}

int countNodes(TreeNode *tempRoot)
{
    if (tempRoot == NULL)
        return 0;
    else
        return countNodes(tempRoot->leftChild) + countNodes(tempRoot->rightChild) + 1;
}

int getNodesCount(binaryTree *tree)
{
    tree->NodesCount = countNodes(root);
    return tree->NodesCount;
}

int calculateHeight(TreeNode *tempRoot)
{
    if (!tempRoot)
        return -1;
    int leftHeight = calculateHeight(tempRoot->leftChild);
    int rightHeight = calculateHeight(tempRoot->rightChild);
    return ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
}

int getHeight(binaryTree *tree)
{
    tree->Height = calculateHeight(root);
    return tree->Height;
}

int findIndex(const int *string, int key, int start, int end)
{
    for (int i = start; i <= end; i++)
        if (string[i] == key)
            return i;

    return -1;
}

TreeNode *buildTree(const int *preOrderString, const int *inOrderString, int inStart, int inEnd)
{
    static int preIndex = 0;
    if (inStart > inEnd)
        return NULL;

    int data = preOrderString[preIndex];
    TreeNode *rootNode = initTreeNode(data);

    int rootIndex = findIndex(inOrderString, data, inStart, inEnd);

    preIndex++;

    rootNode->leftChild = buildTree(preOrderString, inOrderString, inStart, rootIndex - 1);
    rootNode->rightChild = buildTree(preOrderString, inOrderString, rootIndex + 1, inEnd);

    return rootNode;
}

binaryTree *generateTree(const int *preOrderString, const int *inOrderString, int nodes)
{
    binaryTree *tree = initBinaryTree();
    root = buildTree(preOrderString, inOrderString, 0, nodes - 1);
    return tree;
}