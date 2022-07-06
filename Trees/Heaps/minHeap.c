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
    int leftChild = 2*nodeIndex + 1;
    int rightChild = 2*nodeIndex + 2;

    //find the minimum of the two children
    int minimumInd = findMinimum(heap->array, leftChild, rightChild);
    //continue swapping the node with the minimum child as long as node > minimum; 
    while((heap->array)[nodeIndex] > (heap->array)[minimumInd] && minimumInd < heap->size){ //NOTE: NEED TO FIX LAST CONDITION; MAY NOT WORK IF MINIMUMIND = -1
         swap(&(heap->array)[nodeIndex], &(heap->array)[minimumInd]);
         //remember to update the index of the node after swaps with min child
         nodeIndex = minimumInd;
    }
}



//floats up a single element to its correct position; expensive for nodes towards bottom of tree
void floatUp(/* Heap* heap, int nodeIndex */){
    //parent index: (i-1)/2
    //as long as the node is less than the parent AND as long as nodeIndex > 0
    //if node is less than parent, perform a swap
}



int extractMinimum(/* Heap* heap */){
    //check for emptiness
    //return the first element in the array
    //overwrite the first element with the last element in the heap
    //sink down the new root
    //update size
}



int getMinimum(/* Heap* heap */){
    //check for emptiness
    //simply return the first element in the array
}



void decreaseKey(/* Heap*  heap, int nodeIndex, int newVal*/){
    //change the value of the node; it's assumed newVal will be smaller
    //apply the float up operation to the node
}


void deleteNode(/* Heap* heap, int nodeIndex*/){
    //check for emptiness
    //overwrite the node to be deleted with the last element in the heap
    //sink down the element to it's correct spot
    //update size
}


void insertNode(/* Heap* heap, int nodeIndex*/){
    //check for overflow
    //put the node in the next free position in the array
    //float it up to it's correct position
    //update size
}