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

void insertR(TreeNode **tempRoot, int data)
{
    if (*tempRoot == NULL)
    {
        *tempRoot = initTreeNode(data);
    }

    if (data > (*tempRoot)->data)
        insertR(&(*tempRoot)->rightChild, data);
    else if (data < (*tempRoot)->data)
        insertR(&(*tempRoot)->leftChild, data);
}

void insert(binarySearchTree *tree, int data)
{
    insertR(&root, data);
}

TreeNode *findMin(TreeNode *tempRoot)
{
    while (tempRoot->leftChild)
        tempRoot = tempRoot->leftChild;
    return tempRoot;
}

TreeNode *findMax(TreeNode *tempRoot)
{
    while (tempRoot->rightChild)
        tempRoot = tempRoot->rightChild;
    return tempRoot;
}

int getMin(binarySearchTree *tree)
{
    tree->min = findMin(root)->data;
    return tree->min;
}

int getMax(binarySearchTree *tree)
{
    tree->max = findMax(root)->data;
    return tree->max;
}

int findHeight(TreeNode *tempRoot)
{
    if (!tempRoot)
        return -1;
    int leftHeight = findHeight(tempRoot->leftChild);
    int rightHeight = findHeight(tempRoot->rightChild);

    return ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
}

int getHeight(binarySearchTree *tree)
{
    tree->height = findHeight(root);
    return tree->height;
}

int findNodesCount(TreeNode *tempRoot)
{
    return !tempRoot ? 0 : findNodesCount(tempRoot->leftChild) + findNodesCount(tempRoot->rightChild) + 1;
}

int getNodesCount(binarySearchTree* tree){
    tree->nodesCount = findNodesCount(root);
    return tree->nodesCount;
}

int main()
{
    binarySearchTree *tree = initBST();

    root = initTreeNode(5);
    root->leftChild = initTreeNode(3);
    root->rightChild = initTreeNode(7);
    root->leftChild->leftChild = initTreeNode(2);
    root->leftChild->rightChild = initTreeNode(4);
    root->rightChild->rightChild = initTreeNode(8);
    root->rightChild->leftChild = initTreeNode(6);

    preOrder(root);
    printf("\n");
    inOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n%d %d %d %d", getMin(tree), getMax(tree), getHeight(tree), getNodesCount(tree));
    return 0;
}