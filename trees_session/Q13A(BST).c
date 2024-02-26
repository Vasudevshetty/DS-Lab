

#include <stdio.h>
#include <stdlib.h>

// create a structure for node containing data and pointers to right and left child
typedef struct Node
{
    int data;
    struct Node *leftChild;
    struct Node *rightChild;
} node;

// function to initalise node with given data
void initNode(node *Node, int data)
{
    Node->data = data;
    Node->leftChild = Node->rightChild = NULL;
    // this is how a new node gets created later on gets stick on to the tree.
}

// implementing tree using insert function.
node *insert(node *root, int data);

// traversal functions
void preOrder(node *root);
void inOrder(node *root);
void postOrder(node *root);

int main()
{
    node *root = NULL;
    root = insert(root, 1);
    preOrder(root);
    return EXIT_SUCCESS;
}

node *insert(node *root, int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    initNode(newNode, data);
    if (root == NULL)
    {
        root = newNode;
        return root;
    }
    if (root->data < data)
        root->rightChild = insert(root->rightChild, data);
    else if (root->data > data)
        root->leftChild = insert(root->leftChild, data);

    return root;
}

// func definition
void preOrder(node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->leftChild);
        preOrder(root->rightChild);
    }
}
// func definition
void inOrder(node *root)
{
    if (root != NULL)
    {
        preOrder(root->leftChild);
        printf("%d ", root->data);
        preOrder(root->rightChild);
    }
}
// func definition
void postOrder(node *root)
{
    if (root != NULL)
    {
        preOrder(root->leftChild);
        preOrder(root->rightChild);
        printf("%d ", root->data);
    }
}