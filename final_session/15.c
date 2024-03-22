/*Develop a menu driven program to implement Binary Search tree with the followingoperations.
i) Construction ii) Traversals (Pre, In and Post Order) iii) Searching a node by key and deleting if
exists ( node to be deleted may be leaf or non- leaf with one child ortwo children)*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node *initNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

typedef struct Tree
{
    Node *root;
    int height, nodes;
} Tree;

Tree *initTree()
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    if (!tree)
    {
        printf("Memroy allocaiton failed.\n");
        exit(1);
    }
    tree->root = NULL;
    tree->height = tree->nodes = 0;
    return tree;
}

void freeTree(Node *root)
{
    if (!root)
        return;
    freeTree(root->leftChild);
    freeTree(root->rightChild);

    free(root);
}

void preOrder(Node *);
void inOrder(Node *);
void postOrder(Node *);

Node *insert(Node *root, int data);
void constructTree(Tree *tree, int data)
{
    tree->root = insert(tree->root, data);
}

Node *delete(Node *, int);

void deleteKey(Tree *tree, int key)
{
    tree->root = delete (tree->root, key);
}

int main()
{
    Tree *tree = initTree();
    int choice, data, key;
    do
    {
        printf("\nMenu\n");
        printf("1. Insert\n2. Preorder\n3. Inorder\n4. Postorder\n5. Delete key\n6. Exit\n");
        printf("Enter choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &data);
            constructTree(tree, data);
            break;
        case 2:
            preOrder(tree->root);
            break;
        case 3:
            inOrder(tree->root);
            break;
        case 4:
            postOrder(tree->root);
            break;
        case 5:
            printf("Enter key : ");
            scanf("%d", &key);
            deleteKey(tree, key);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
            break;
        }
        printf("\n");
    } while (choice != 6);
    return 0;
}

Node *getMax(Node *root)
{ // inorder successor
    while (root && root->rightChild)
        root = root->rightChild;

    return root;
}

Node *getMin(Node *root)
{ // inorder predecsoor.
    while (root && root->leftChild)
        root = root->leftChild;

    return root;
}

int getHeight(Node *root)
{
    if (!root)
        return -1;

    int leftHeight = getHeight(root->leftChild);
    int rightHeight = getHeight(root->rightChild);

    return (rightHeight > leftHeight ? rightHeight : leftHeight) + 1;
}

Node *delete(Node *root, int key)
{
    if (!root)
        return NULL;
    if (key < root->data)
        root->leftChild = delete (root->leftChild, key);
    else if (key > root->data)
        root->rightChild = delete (root->rightChild, key);
    else
    {
        if (!root->rightChild)
        {
            Node *temp = root->leftChild;
            free(root);
            return temp;
        }
        else if (!root->leftChild)
        {
            Node *temp = root->rightChild;
            free(root);
            return temp;
        }
        Node *temp = getMin(root->rightChild);
        root->data = temp->data;
        root->rightChild = delete (root->rightChild, temp->data);
    }
    return root;
}

Node *insert(Node *root, int data)
{
    if (!root)
        return initNode(data);

    if (data < root->data)
        root->leftChild = insert(root->leftChild, data);
    else
        root->rightChild = insert(root->rightChild, data);

    return root;
}

void preOrder(Node *root)
{
    if (root)
    {
        printf("%d ", root->data);
        preOrder(root->leftChild);
        preOrder(root->rightChild);
    }
}

void inOrder(Node *root)
{
    if (root)
    {
        inOrder(root->leftChild);
        printf("%d ", root->data);
        inOrder(root->rightChild);
    }
}

void postOrder(Node *root)
{
    if (root)
    {
        postOrder(root->leftChild);
        postOrder(root->rightChild);
        printf("%d ", root->data);
    }
}
