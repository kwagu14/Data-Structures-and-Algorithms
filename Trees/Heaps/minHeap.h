#ifndef MINHEAP_H
#define MINHEAP_H

#include "heapUtils.h"


//this heapifies a single subtree 
void minHeapify(Heap* heap, int nodeIndex );



void buildMinHeap(Heap* heap);


//sinks down a single element to its correct position; expensive for nodes high in tree
void sinkDown(Heap* heap, int nodeIndex);



//floats up a single element to its correct position; expensive for nodes towards bottom of tree
void floatUp(/* Heap* heap, int nodeIndex */);


int extractMinimum(/* Heap* heap */);



int getMinimum(/* Heap* heap */);



void decreaseKey(/* Heap*  heap, int nodeIndex, int newVal*/);


void deleteNode(/* Heap* heap, int nodeIndex*/);


void insertNode(/* Heap* heap, int nodeIndex*/);

#endif