#include "utils.h"



void printArray(int* array, int size){

    for(int i = 0; i < size; i++){
        printf("%d\t", array[i]);
    }
    printf("\n");
}



void swap(int* element1, int* element2){
    //save the value of element1
    int temp = *element1;
    *element1 = *element2;
    *element2 = temp;
}