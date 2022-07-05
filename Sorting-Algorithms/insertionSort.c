#include "utils.h"



void insertionSort(int* array, int size){

    for(int i = 1; i < size; i++){
        int currentElement = array[i];
        int j = i - 1;

        while(j >= 0 && currentElement < array[j]){
            array[j+1] = array[j];
            j = j - 1; 
        }
        array[j+1] = currentElement;
    }

}



int main(){

    int arraySize = 8;
    int array[] = {3, 9, 1, 2, 0, 7, 8, 9};

    printf("The unsorted array is: \n");
    printArray(array, arraySize);

    //call insertion sort
    insertionSort(array, arraySize);


    printf("The array after sorting: \n");
    printArray(array, arraySize);


    return 0; 
}