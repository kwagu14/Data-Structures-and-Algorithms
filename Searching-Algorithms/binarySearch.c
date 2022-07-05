#include <stdlib.h>
#include <stdio.h>



int binarySearch(int* intArr, int size, int target){

    int start = 0; 
    int end = size - 1; 
    int mid;

    while(start <= end){
        mid = (start + end) / 2;
        if(intArr[mid] == target){
            return mid;
        }else if(target > intArr[mid]){
            start = mid+1;
        }else{
            end = mid-1; 
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
    int target = 7;
    int targetIndex;

    //Here is a sample array
    int intArray[] = {1, 2, 3, 3, 4, 5, 7, 9};

    //print the array
    printf("The target is %d. Here is the test array: \n", target);
    printArray(intArray, arraySize);

    //perform binary search 
    targetIndex = binarySearch(intArray, arraySize, target);

    //print the result
    printf("The target was found at index %d", targetIndex);


}