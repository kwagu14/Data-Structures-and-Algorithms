#include <stdlib.h>
#include <stdio.h>



int linearSearch(int* intArr, int size, int target){

    for(int i = 0; i < size; i++){

        if(intArr[i] == target){
            return i;
        }

    }
    return -1;

}


void printArray(int* intArr, int size){

    for(int i = 0; i < size; i++){
        printf("%d\t", intArr[i]);
    }
    printf("\n");

}


int main(){

    int arraySize = 8;
    int target = 4;
    int targetIndex;

    //Here is a sample array
    int intArray[] = {8, 2, 9, 7, 4, 2, 1, 5};

    //print the array
    printf("The target is %d. Here is the test array: \n", target);
    printArray(intArray, arraySize);

    //perform linear search 
    targetIndex = linearSearch(intArray, arraySize, target);

    //print the result
    printf("The target was found at index %d", targetIndex);


}