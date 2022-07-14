#include "../../utils.h"
#include "../../Trees/Heaps/heapUtils.h"
#include "../../Trees/Heaps/maxHeap.h"


void heapSort(Heap* heap){ 
    //while there are still elements in the heap
    while(heap -> size > 1){
        int maximum = extractMaximum(heap);
        (heap->array)[heap->size] = maximum;
    }  
}



int main(){

    //create an array with all of the data inside
    int data[100] = {2, 8, 4, 9, 3, 6, 5, 7, 1, 0};
    int dataSize = 10;
    //initialize a heap and set the dataset to the array
    Heap* heap = initializeHeap(100, data, 10);
    //call build max heap
    buildMaxHeap(heap);
    //call heapsort
    heapSort(heap);
    printf("The sorted array: \n");
    //print the final array
    printArray(heap->array, dataSize);


    return 0; 
}