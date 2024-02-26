#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treeNode
{
    int data;
    struct treeNode *leftChild;
    struct treeNode *rightChild;
} TreeNode;

TreeNode *initTreeNode(int data)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (!newNode)
    {
        printf("Memory alocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

typedef struct Node
{
    TreeNode *nodeData;
    struct Node *next;
} node;

node *initNode(TreeNode *nodeData)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->nodeData = nodeData;
    newNode->next = NULL;
    return newNode;
}

typedef struct
{
    node *Top;
    int Length;
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
    stack->Length = 0;
    return stack;
}

#define top stack->Top
#define length stack->Length

bool isEmpty(Stack *stack)
{
    return !(top && length);
}

void push(Stack *stack, TreeNode *nodeData)
{
    node *newNode = initNode(nodeData);
    newNode->next = top;
    top = newNode;
    length++;
}

TreeNode *pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack empty, popping failed.\n");
        return NULL;
    }
    node *toDelete = top;
    TreeNode *nodeData = top->nodeData;
    top = top->next;
    free(toDelete);
    length--;
    return nodeData;
}

TreeNode *peek(Stack *stack)
{
    return isEmpty(stack) ? NULL : top->nodeData;
}

typedef struct
{
    node *Front;
    node *Rear;
    int Count;
} Queue;

Queue *initQueue()
{
    Queue *que = (Queue *)malloc(sizeof(Queue));
    if (!que)
    {
        printf("Memory allcoation failed.\n");
        exit(1);
    }
    que->Front = que->Rear = NULL;
    que->Count = 0;
    return que;
}

#define front que->Front
#define rear que->Rear
#define count que->Count

bool isEmptyQueue(Queue *que)
{
    return !(front && rear && count);
}

void enqueue(Queue *que, TreeNode *nodeData)
{
    node *newNode = initNode(nodeData);
    if (isEmptyQueue(que))
        front = rear = newNode;
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

TreeNode *dequeue(Queue *que)
{
    if (isEmptyQueue(que))
    {
        printf("Empty queue, dequeueing failed.\n");
        return NULL;
    }
    node *toDelete = front;
    TreeNode *nodeData = toDelete->nodeData;
    if (front == rear)
        front = rear = NULL;
    front = toDelete->next;
    free(toDelete);
    count--;
    return nodeData;
}

void inOrder(TreeNode *root)
{
    if (root)
    {
        inOrder(root->leftChild);
        printf("%d ", root->data);
        inOrder(root->rightChild);
    }
}

void preOrder(TreeNode *root)
{
    if (root)
    {
        printf("%d ", root->data);
        preOrder(root->leftChild);
        preOrder(root->rightChild);
    }
}

void postOrder(TreeNode *root)
{
    if (root)
    {
        postOrder(root->leftChild);
        postOrder(root->rightChild);
        printf("%d ", root->data);
    }
}