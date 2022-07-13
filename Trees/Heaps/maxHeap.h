#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "heapUtils.h"


void maxHeapify(Heap* heap, int nodeIndex);

void buildMaxHeap(Heap* heap);

void floatUp(Heap* heap, int nodeIndex);

int extractMaximum(Heap* heap);

int getMaximum(Heap* heap);

void increaseKey(Heap*  heap, int nodeIndex, int newVal);

void deleteNode(Heap* heap, int nodeIndex);

void insertNode(Heap* heap, int nodeIndex);

#endif