#include "utils.h"



int partition(int* array, int start, int end){
    //always choose the last element as the pivot
    int pivot = array[end]; 
    //This is the index of the last element smaller than the pivot
    int currentPivIndex = start - 1;

    for(int j = start; j < end; j++){
        //if the element is smaller than the pivot
        if( array[j] <= pivot){
            //increment i (marks the end of the 'small' side)
            currentPivIndex++;
            //move the small element where it should be in the array. 
            swap(&array[currentPivIndex], &array[j]);
        }
    }
    //move the pivot to the correct place
    swap(&array[currentPivIndex+1], &array[end]);
    return currentPivIndex+1; 
}



void quicksort(int* array, int start, int end){

    if(start < end){
        int partitionIndex = partition(array, start, end);
        //call quicksort recursively on both halves of the array 
        quicksort(array, start, partitionIndex-1); 
        quicksort(array, partitionIndex+1, end);
    }

}



int main(){

    int arraySize = 8;
    int array[] = {3, 9, 1, 2, 0, 7, 8, 9};

    printf("The unsorted array is: \n");
    printArray(array, arraySize);

    //call quicksort
    quicksort(array, 0, arraySize - 1);

    printf("The array after sorting: \n");
    printArray(array, arraySize);


    return 0; 
}