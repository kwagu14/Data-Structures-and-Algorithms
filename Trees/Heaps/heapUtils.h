#ifndef HEAPUTILS_H
#define HEAPUTILS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Heap{
    int* array; 
    int maxCapacity;
    int size;
} Heap;

Heap* initializeHeap(int maxCapacity, int* dataset);

int findMinimum(int* array, int ind1, int ind2);

int findMaximum(int* array, int ind1, int ind2);

#endif