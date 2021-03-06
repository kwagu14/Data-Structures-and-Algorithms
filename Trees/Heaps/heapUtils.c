/****************************** MAXIMUM AND MINIMUM FUNCTIONS ********************************/
#include "heapUtils.h"

//initializes an empty heap data structure
Heap* initializeHeap(int maxCapacity, int* dataset, int dataSize){
    Heap* newHeap = (Heap*) malloc(sizeof(Heap));
    newHeap -> maxCapacity = maxCapacity;
    newHeap -> size = dataSize; 
    newHeap -> array = dataset;
}



//Takes in two indices and finds which element in the array has the smaller value
int findMinimum(int* array, int ind1, int ind2){
    int minimumInd;
    if(array[ind1] <= array[ind2]){
        minimumInd = ind1;
    }else{
        minimumInd = ind2;
    }
    return minimumInd;
}



//Takes in two indices and finds which element in the array has the greater value
int findMaximum(int* array, int ind1, int ind2){
    int maximumInd;
    if(array[ind1] >= array[ind2]){
        maximumInd = ind1;
    }else{
        maximumInd = ind2;
    }
    return maximumInd;
}