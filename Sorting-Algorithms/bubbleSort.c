#include "utils.h"



void bubbleSort(int* array, int size){

    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(array[j] > array[j+1]){
                swap(&array[j], &array[j+1]);
            }
        }
    }

}



int main(){

    int arraySize = 8;
    int array[] = {3, 9, 1, 2, 0, 7, 8, 9};

    printf("The unsorted array is: \n");
    printArray(array, arraySize);

    //call bubble sort
    bubbleSort(array, arraySize);

    printf("The array after sorting: \n");
    printArray(array, arraySize);


    return 0; 
}