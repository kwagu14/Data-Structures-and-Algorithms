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

typedef struct Queue{
    int start; 
    int end; 
    int size;
    int capacity;
    Node** array;
} Queue;


Node* InitializeNode(int key, Node* parent);


Queue* createQueue(int capacity);

int isFull(Queue* queue);

int isEmpty(Queue* queue);

void enqueue(Queue* queue, Node* node);

void dequeue(Queue* queue);

Node* peek(Queue* queue);

#endif