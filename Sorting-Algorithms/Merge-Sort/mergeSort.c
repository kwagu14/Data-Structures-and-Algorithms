#include "../../utils.h"



void merge(int* array, int start, int mid, int end){

    //CREATE COMPONENT ARRAYS
    
    //add 1 since we're including the middle element
    int sizeLeft = mid - start +1;
    int sizeRight = end - mid;
    int left[sizeLeft];
    int right[sizeRight];

    for(int i = 0; i < sizeLeft; i++){
        left[i] = array[start + i]; 
    }
    for(int i = 0; i < sizeRight; i++){
        //Add one since mid is not included in this array (we must go 1 over)
        right[i] = array[mid+1 + i];
    }

    //FILL IN THE COMPOSITE ARRAY IN SORTED ORDER
    
    int i = 0; int j = 0; int k = start; 

    while(i < sizeLeft && j < sizeRight){
        if(left[i] <= right[j]){
            array[k] = left[i];
            i++; 
        }else{
            array[k] = right[j];
            j++;
        }
        k++;
    }

    while(i < sizeLeft){
        array[k] = left[i];
        k++; 
        i++; 
    }
    while(j < sizeRight){
        array[k] = right[j];
        k++;
        j++; 
    }
    

}



void mergeSort(int* array, int start, int end){


    //this is when recursion stops
    if(start < end){
        
        //calculate the middle
        int mid = (start + end)/2;

        //call mergesort recursively on the two halves
        mergeSort(array, start, mid);
        mergeSort(array, mid + 1, end);

        //merge the two arrays
        merge(array, start, mid, end);
    }
}



int main(){

    int arraySize = 8;
    int array[] = {3, 9, 1, 2, 0, 7, 8, 9};

    printf("The unsorted array is: \n");
    printArray(array, arraySize);

    //call merge sort
    mergeSort(array, 0, arraySize-1);


    printf("The array after sorting: \n");
    printArray(array, arraySize); 


    return 0;
}