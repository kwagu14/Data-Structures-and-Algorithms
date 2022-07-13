/* Program for implementing a max heap data structure */
#include "heapUtils.h"
#include "../../utils.h"



//this heapifies a single subtree 
void minHeapify(Heap* heap, int nodeIndex ){

    int leftChild = 2*nodeIndex + 1;
    int rightChild = 2*nodeIndex + 2;

    //MAKE SURES THESE VALUES ARE WITHIN BOUNDS!
    if(leftChild >= heap -> size){
        //if not in bounds, set the child to -1.
        leftChild = -1;
    }
    if(rightChild >= heap -> size){
        rightChild = -1;
    } 

    //now find the minimum of the two children
    int smallestInd = findMinimum(heap->array, leftChild, rightChild);
    //if smallest is less than the current node, perform a swap between node and smallest
    if((heap->array)[smallestInd] < (heap->array)[nodeIndex]){
        swap(&(heap->array)[smallestInd], &(heap->array)[nodeIndex]);
        //sink down the swapped node to it's correct position
        sinkDown(heap, smallestInd);
    }

}



void buildMinHeap(Heap* heap){

    //start at rightmost non-leaf node, which is (size/2) - 1. 
    int start = ((heap -> size)/2) - 1;

    //Do for all subtrees; since the data is arranged in an array, all parents can be accessed by traversing the array backwards  
    for(int i = start; i >= 0; --i){
        minHeapify(heap, i);
    }

}



//sinks down a single element to its correct position; expensive for nodes high in tree
void sinkDown(Heap* heap, int nodeIndex){
    int leftChild;
    int rightChild;
    int minimumInd;

    //continue swapping the node with the minimum child as long as node > minimum; 
    while((heap->array)[nodeIndex] > (heap->array)[minimumInd] && minimumInd < heap->size){ //NOTE: NEED TO FIX LAST CONDITION; MAY NOT WORK IF MINIMUMIND = -1
        int leftChild = 2*nodeIndex + 1;
        int rightChild = 2*nodeIndex + 2;
        minimumInd = findMinimum(heap->array, leftChild, rightChild);
        swap(&(heap->array)[nodeIndex], &(heap->array)[minimumInd]);
        //remember to update the index of the node after swaps with min child
        nodeIndex = minimumInd;
    }
}



//floats up a single element to its correct position; expensive for nodes towards bottom of tree
void floatUp(Heap* heap, int nodeIndex){
    int parentIndex;
    //as long as the node is less than the parent AND nodeIndex > 0
    while((heap->array)[nodeIndex] < (heap->array)[parentIndex] && nodeIndex > 0){
        parentIndex = (nodeIndex-1)/2;
        //perform a swap and update the nodeIndex to parent
        swap(&(heap->array)[nodeIndex], &(heap->array)[parentIndex]);
        nodeIndex = parentIndex;
    }
}



int extractMinimum(Heap* heap){
    //make sure something is in the heap
    if(heap -> size > 0){
        int minimum = (heap -> array)[0];
        int heapSize = heap->size;
        //overwrite the first element with the last element in the heap
        (heap -> array)[0] = (heap -> array)[heapSize-1];
        //sink down the new root
        sinkDown(heap, 0);
        //update size
        --(heap -> size);
        return minimum;
    }else{
        printf("Cannot extract minimum. Nothing is within the heap.\n");
    }
}



int getMinimum(Heap* heap){
    //make sure something is in the heap
    if(heap -> size > 0){
        //simply return the first element in the array
        return (heap->array)[0];
    }else{
        printf("Cannot get the minimum. Nothing is within the heap.\n");
    }
}



void decreaseKey(Heap*  heap, int nodeIndex, int newVal){
    //change the value of the node; it's assumed newVal will be smaller
    (heap->array)[nodeIndex] = newVal;
    //apply the float up operation to the node
    floatUp(heap, nodeIndex);
}


void deleteNode(Heap* heap, int nodeIndex){
    //make sure something is in the heap
    if(heap -> size > 0){
        int heapSize = heap->size;
        //overwrite the node to be deleted with the last element in the heap
        (heap->array)[nodeIndex] = (heap->array)[heapSize-1];
        //sink down the element to it's correct spot
        sinkDown(heap, nodeIndex);
        //update size
        --(heap -> size);
    }else{
        printf("Cannot delete the item. Nothing is within the heap.\n");
    }
}


void insertNode(Heap* heap, int value){
    //check for overflow
    if(heap -> size == heap -> maxCapacity){
        printf("Cannot add the node in the heap. There is not enough space.\n");
    }else{
        //put the node in the next free position in the array
        (heap->array)[heap->size] = value;
        //float it up to it's correct position
        floatUp(heap, heap->size);
        //update size
        ++(heap -> size);
    }
}


int main(){

    int data[100] = {3, 8, 2, 9, 8, 2, 4, 1, 0, 0, 1, 8};

    Heap* heap = initializeHeap(100, data);



    return 0;
}