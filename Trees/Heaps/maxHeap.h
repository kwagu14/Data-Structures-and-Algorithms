#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "heapUtils.h"

//this heapifies a single subtree 
void maxHeapify(/* Heap* heap, int nodeIndex */);



void buildMaxHeap(/* Heap* heap */);



//sinks down a single element to its correct position; expensive for nodes high in tree
void sinkDown(/* Heap* heap, int node */);



//floats up a single element to its correct position; expensive for nodes towards bottom of tree
void floatUp(/* Heap* heap, int nodeIndex */);


int extractMaximum(/* Heap* heap */);



int getMaximum(/* Heap* heap */);



void increaseKey(/* Heap*  heap, int nodeIndex, int newVal*/);


void deleteNode(/* Heap* heap, int nodeIndex*/);


void insertNode(/* Heap* heap, int nodeIndex*/);

#endif