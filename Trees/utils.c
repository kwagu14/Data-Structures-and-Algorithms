/*
    Some utilities to aid with the tree programs
*/

#include "utils.h"


//NODE QUEUE: QUEUE THAT WORKS WITH NODES

Queue* createQueue(int capacity){
    Queue* queue = (Queue*) malloc(sizeof(Queue)); 
    //set all of the properties for bookkeeping 
    queue -> capacity = capacity; 
    queue -> start = 0; 
    queue -> end = 0; 
    //create an array of the correct size
    queue -> array = (GeneralNode**) malloc(capacity * sizeof(GeneralNode*));
    return queue;
}



int isFull(Queue* queue){
    return queue -> end == queue -> capacity;
}



int isEmpty(Queue* queue){
    return queue -> start == queue -> end;
}



//adds element to the end of the queue
void enqueue(Queue* queue, GeneralNode* node){
    //if queue not full, we can procede with adding something
    if(isFull(queue)){
        printf("Can't add item to the queue. It is full.\n");
    }else{
        //add the number to the next free position in the array
        GeneralNode** queueArray = queue -> array;
        queueArray[queue->end] = node;
        //update the size and the end of the queue
        ++(queue -> end);
    }

}



//removes element from the front of the queue
void dequeue(Queue* queue){
    GeneralNode** queueArr = queue -> array;
    //if queue empty, we can't remove anything
    if(isEmpty(queue)){
        printf("There is nothing in the queue to remove.\n");
    }else{
        for(int i = 0; i < queue -> capacity - 1; i++){
            queueArr[i] = queueArr[i + 1];
        } 
        //overwrite the last element with 0, for good measure
        queueArr[queue -> end] = 0; 
        --(queue -> end);
    }
}



GeneralNode* peek(Queue* queue){
    GeneralNode** queueArr = queue -> array; 
    return queueArr[queue -> start]; 
}