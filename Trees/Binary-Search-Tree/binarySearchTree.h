#ifndef TREEUTILS_H
#define TREEUTILS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node* rightChild;
    struct Node* leftChild; 
    struct Node* parent; 
}Node;

typedef struct Queue{
    int start; 
    int end; 
    int size;
    int capacity;
    Node** array;
} Queue;


Node* initializeNode(int key, Node* parent);

Queue* createQueue(int capacity);

Node* insertNode(int key, Node* current, Node* parent);

void deleteNode(Node* root, int key);

Node* findSuccessor(int key, Node* root);

Node* findPredecessor(int key, Node* root);

Node* findMinimum(Node* root);

Node* findMaximum(Node* root);

Node* search(int key, Node* root);

void printTreeInorder(Node* root);

void enqueueChildren(Queue* queue, Node* parent);

void printTreeLevelOrder(Node* parent);

int isFull(Queue* queue);

int isEmpty(Queue* queue);

void enqueue(Queue* queue, Node* node);

void dequeue(Queue* queue);

Node* peek(Queue* queue);

#endif