#ifndef TREEUTILS_H
#define TREEUTILS_H

#include <stdio.h>
#include <stdlib.h>


typedef struct Node {

    struct GeneralNode* leftmostChild;
    struct GeneralNode* nextSibling;
    int data;

} Node;


typedef struct Queue{
    int start; 
    int end; 
    int size;
    int capacity;
    Node** array;
} Queue;


Queue* createQueue(int capacity);

int isFull(Queue* queue);

int isEmpty(Queue* queue);

void enqueue(Queue* queue, Node* node);

void dequeue(Queue* queue);

Node* peek(Queue* queue);

#endif