#ifndef FIFO_H
#define FIFO_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Queue{
    int start; 
    int end; 
    int size;
    int capacity;
    int* array;
} Queue;


Queue* createQueue(int capacity);

int isFull(Queue* queue);

int isEmpty(Queue* queue);

void enqueue(Queue* queue, int num);

void dequeue(Queue* queue);

int peek(Queue* queue);

void printQueue(Queue* queue);

#endif