#include <stdio.h>
#include<stdlib.h>
#include"traversals.h"

typedef struct {
    binaryTree *Tree;
    int max, min;
} binarySearchTree;

#define root tree->Tree->Root

binarySearchTree* initBinarySearchTree(){
    binarySearchTree *tree = (binarySearchTree *)malloc(sizeof(binarySearchTree));
    if(!tree){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    tree->Tree = initBinaryTree();
    tree->max = tree->min = 0;
    return tree;
}



