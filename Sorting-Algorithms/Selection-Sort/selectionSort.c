#include "../../utils.h"



void selectionSort(int* array, int size){

    int minIndex;

    for(int i = 0; i < size-1; i++){
        minIndex = i;
        for(int j = i+1; j < size; j++){
            if(array[j] < array[minIndex]){
                minIndex = j;
            }
        }
        swap(&array[minIndex], &array[i]);
    }

}



int main(){

    int arraySize = 8;
    int array[] = {3, 9, 1, 2, 0, 7, 8, 9};

    printf("The unsorted array is: \n");
    printArray(array, arraySize);

    //call selection sort
    selectionSort(array, arraySize);

    printf("The array after sorting: \n");
    printArray(array, arraySize);


    return 0; 
}