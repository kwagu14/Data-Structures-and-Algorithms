#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>


typedef struct GeneralNode {

    struct GeneralNode* leftmostChild;
    struct GeneralNode* nextSibling;
    int data;

} GeneralNode;


typedef struct Queue{
    int start; 
    int end; 
    int size;
    int capacity;
    GeneralNode** array;
} Queue;


Queue* createQueue(int capacity);

int isFull(Queue* queue);

int isEmpty(Queue* queue);

void enqueue(Queue* queue, GeneralNode* node);

void dequeue(Queue* queue);

GeneralNode* peek(Queue* queue);

#endif