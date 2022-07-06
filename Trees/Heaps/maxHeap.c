/* Program for implementing a max heap data structure */
/* very similar to min heap; comparison signs have changed */
#include "heapUtils.h"


//this heapifies a single subtree 
void maxHeapify(/* Heap* heap, int nodeIndex */){

    //left child: 2*nodeIndex + 1
    //right child: 2*nodeIndex + 2

    //MAKE SURES THESE VALUES ARE WITHIN BOUNDS! (leftChild < heap.size and rightChild < heap.size)
    //if not in bounds, set the child to -1. 

    //now find the maximum of the two children (largest)
    //if largest is less than the current node, perform a swap between node and largest
    //else, do nothing. The subtree is already fixed

}



void buildMaxHeap(/* Heap* heap */){

    //start at rightmost non-leaf node, which is (size/2) - 1. Perform heapify on this subtree.
    //Do this on all the remaining subtrees.
    //since the data is arranged in an array, all of the parents can be accessed simply by decrementing the node index each time to traverse the array backwards  

}



//sinks down a single element to its correct position; expensive for nodes high in tree
void sinkDown(/* Heap* heap, int node */){
    //left child: 2*nodeIndex + 1
    //right child: 2*nodeIndex + 2

    //find the minimum of the two children
    //compare the node to the minimum. If greater than minimum, swap
    //continue this process until the comparison fails [while(node < minimum)]
    //remember to update the index of the node after swaps. Will take on the left or right child index
}



//floats up a single element to its correct position; expensive for nodes towards bottom of tree
void floatUp(/* Heap* heap, int nodeIndex */){
    //parent index: (i-1)/2
    //as long as the node is greater than the parent AND as long as nodeIndex > 0
    //if node is greater than parent, perform a swap
}



int extractMaximum(/* Heap* heap */){
    //check for emptiness
    //return the first element in the array
    //overwrite the first element with the last element in the heap
    //sink down the new root
    //update size

}



int getMaximum(/* Heap* heap */){
    //check for emptiness
    //simply return the first element in the array
}



void increaseKey(/* Heap*  heap, int nodeIndex, int newVal*/){
    //change the value of the node; it's assumed newVal will be greater
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