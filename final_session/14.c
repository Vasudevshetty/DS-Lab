/*Develop a menu driven program to implement Binary Search tree with the followingoperations.
i) Construction ii) Traversals (Pre, In and Post Order) iii) Searching a node by key and displaying its
information along with its parent if exists, otherwise a suitablemessage. iv)Counting all nodes. v)
Finding height. vi Finding node with the Maximum key value and printing the node details along
with the parent*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void inOrder(Node *);
void preOrder(Node *);
void postOrder(Node *);

Tree *constructTree(Tree *, int);
Node *insert(Node *, int);

int calculateHeight(Node *);
int calculateNodesCount(Node *);

bool search(Node *, Node *, int);
int getMax(Node *, Node *);

int main()
{
    Tree *tree = initTree();
    int choice, data, key;

    do
    {
        printf("\nMenu\n");
        printf("1. Insert\n2. Preorder\n3. Inorder\n4. Postorder\n");
        printf("5. Height\n6. Nodes Count\n7. Search key\n8. Maximum Element\n");
        printf("9. Exit\nEnter choice : ");
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
            printf("Height of the tree is %d\n", tree->height);
            break;
        case 6:
            printf("Nodes count of the tree is %d\n", tree->nodes);
            break;
        case 7:
            printf("Enter key : ");
            scanf("%d", &key);
            search(tree->root, tree->root, key) ? printf("key found\n") : printf("key not found\n");
            break;
        case 8:
            getMax(tree->root, tree->root);
            break;
        case 9:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
            break;
        }
        printf("\n");
    } while (choice != 9);
    freeTree(tree->root);
    free(tree);
    return 0;
}

int getMax(Node *root, Node *parent)
{
    if (!root)
    {
        printf("Tree is empty\n");
        return -1;
    }

    while (root->rightChild)
    {
        parent = root;
        root = root->rightChild;
    }

    printf("The maximum value is %d\n", root->data);
    if (parent && parent != root)
        printf("The parent of the maximum value is %d\n", parent->data);

    return root->data;
}

bool search(Node *root, Node *parent, int key)
{
    if (!root)
        return false;

    if (root->data == key)
    {
        if (parent && parent != root)
            printf("Parent is %d\n", parent->data);
        return true;
    }

    if (key < root->data)
        return search(root->leftChild, root, key);
    else if (key > root->data)
        return search(root->rightChild, root, key);

    return false;
}

int calculateNodesCount(Node *root)
{
    if (!root)
        return 0;
    return calculateNodesCount(root->leftChild) + calculateNodesCount(root->rightChild) + 1;
}

int calculateHeight(Node *root)
{
    if (!root)
        return -1;

    int leftHeight = calculateHeight(root->leftChild);
    int rightHeight = calculateHeight(root->rightChild);

    return (rightHeight > leftHeight ? rightHeight : leftHeight) + 1;
}

Tree *constructTree(Tree *tree, int data)
{
    tree->root = insert(tree->root, data);
    tree->height = calculateHeight(tree->root);
    tree->nodes = calculateNodesCount(tree->root);
    return tree;
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
