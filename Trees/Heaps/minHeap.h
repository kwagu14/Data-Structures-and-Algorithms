#ifndef MINHEAP_H
#define MINHEAP_H

#include "heapUtils.h"


void minHeapify(Heap* heap, int nodeIndex );

void buildMinHeap(Heap* heap);

void floatUp(Heap* heap, int nodeIndex);

int extractMinimum(Heap* heap);

int getMinimum(Heap* heap);

void decreaseKey(Heap*  heap, int nodeIndex, int newVal);

void deleteNode(Heap* heap, int nodeIndex);

void insertNode(Heap* heap, int nodeIndex);

#endif