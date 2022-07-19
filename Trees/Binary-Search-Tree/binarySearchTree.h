#ifndef TREEUTILS_H
#define TREEUTILS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    Node* rightChild;
    Node* leftChild; 
    Node* parent; 
} Node; 


Node* InitializeNode(int key);

#endif