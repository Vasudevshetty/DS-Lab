#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

typedef struct
{
    TreeNode *Root;
    int min, max;
    int height, nodesCount;
} binarySearchTree;

#define root tree->Root

binarySearchTree *initBST()
{
    binarySearchTree *tree = (binarySearchTree *)malloc(sizeof(binarySearchTree));
    if (!tree)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    root = NULL;
    tree->max = tree->min = 0;
    tree->height = -1;
    tree->nodesCount = 0;
    return tree;
}

void insertR(TreeNode **node, int data)
{
    if (*node == NULL)
    {
        *node = initTreeNode(data);
    }

    if (data > (*node)->data)
        insertR(&(*node)->rightChild, data);
    else if (data < (*node)->data)
        insertR(&(*node)->leftChild, data);
}

void insert(binarySearchTree *tree, int data)
{
    insertR(&root, data);
}

int main()
{
    binarySearchTree *tree = initBST();
    int elements[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < n; i++)
    {
        insert(tree, elements[i]);
    }
    preOrder(root);
    printf("\n");
    inOrder(root);
    printf("\n");
    postOrder(root);
    return 0;
}