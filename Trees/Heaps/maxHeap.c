/* Program for implementing a minimum heap data structure */
#include "heapUtils.h"
#include "../../utils.h"



//this heapifies a single subtree 
void maxHeapify(Heap* heap, int nodeIndex ){
    int* heapArr = heap -> array;
    int largest = nodeIndex;
    int leftChild = 2*nodeIndex + 1;
    int rightChild = 2*nodeIndex + 2;

    //MAKE SURES THESE CHILDREN ARE WITHIN BOUNDS!
    if(leftChild < heap->size && heapArr[leftChild] > heapArr[largest]){
        largest = leftChild;
    }
    if(rightChild < heap->size && heapArr[rightChild] > heapArr[largest]){
        largest = rightChild;
    }

    //if largest is less than the current node, perform a swap between node and smallest
    if(largest != nodeIndex){
        swap(&heapArr[largest], &heapArr[nodeIndex]);
        //sink down the swapped node to it's correct position
        maxHeapify(heap, largest);
    }

}



void buildMaxHeap(Heap* heap){

    //start at rightmost non-leaf node, which is (size/2) - 1. 
    int start = ((heap -> size)/2) - 1;
    //Do for all subtrees; since the data is arranged in an array, all parents can be accessed by traversing the array backwards  
    for(int i = start; i >= 0; --i){
        maxHeapify(heap, i);
    }

}



//floats up a single element to its correct position; expensive for nodes towards bottom of tree
void floatUp(Heap* heap, int nodeIndex){
    int parentIndex = (nodeIndex-1)/2;
    //as long as the node is greater than the parent AND nodeIndex > 0
    while(nodeIndex > 0 && (heap->array)[nodeIndex] > (heap->array)[parentIndex]){
        //perform a swap and update the nodeIndex to parent
        swap(&(heap->array)[nodeIndex], &(heap->array)[parentIndex]);
        nodeIndex = parentIndex;
        parentIndex = (nodeIndex-1)/2;
    }
}



int extractMaximum(Heap* heap){
    //make sure something is in the heap
    if(heap -> size > 0){
        int maximum = (heap -> array)[0];
        int heapSize = heap->size;
        //overwrite the first element with the last element in the heap
        (heap -> array)[0] = (heap -> array)[heapSize-1];
        //sink down the new root
        maxHeapify(heap, 0);
        //update size
        --(heap -> size);
        return maximum;
    }else{
        printf("Cannot extract maximum. Nothing is within the heap.\n");
    }
}



int getMaximum(Heap* heap){
    //make sure something is in the heap
    if(heap -> size > 0){
        //simply return the first element in the array
        return (heap->array)[0];
    }else{
        printf("Cannot get the maximum. Nothing is within the heap.\n");
    }
}



void increaseKey(Heap*  heap, int nodeIndex, int newVal){
    //change the value of the node; it's assumed newVal will be larger
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
        maxHeapify(heap, nodeIndex);
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


// int main(){

//     int data[100] = {3, 8, 1, 9, 4, 2, 7, 5, 6, 0};
//     int dataSize = 10;

//     Heap* heap = initializeHeap(100, data, dataSize);
//     buildMaxHeap(heap);
//     printf("The heapified array: \n");
//     printArray(heap->array, heap->size);
//     printf("Extracting the maximum: \n");
//     extractMaximum(heap);
//     printArray(heap->array, heap->size);
//     printf("The new maximum value: \n"); 
//     printf("%d\n", getMaximum(heap));
//     printf("Increasing the value of element 5. Old value: %d, new value: 11\n", (heap->array)[5]);
//     increaseKey(heap, 5, 11);
//     printArray(heap->array, heap->size);
//     printf("deleting the 5th node. Value = %d\n", (heap->array)[5]);
//     deleteNode(heap, 5);
//     printArray(heap->array, heap->size);
//     printf("inserting a node into the heap. Value = 10:\n");
//     insertNode(heap, 10);
//     printArray(heap->array, heap->size);


//     return 0;
// }