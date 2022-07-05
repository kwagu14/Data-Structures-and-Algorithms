/*
    Simple implementation of a FIFO queue using an array
*/
#include "fifo.h"

typedef struct Queue{
    int start; 
    int end; 
    int size;
    int capacity;
    int* array;
} Queue;


Queue* createQueue(int capacity){
    Queue* queue = (Queue*) malloc(sizeof(Queue)); 

    //set all of the properties for bookkeeping 
    queue -> capacity = capacity; 
    queue -> start = 0; 
    queue -> end = 0; 
    //create an array of the correct size
    queue -> array = (int*) malloc(capacity * sizeof(int));

    return queue;
}



int isFull(Queue* queue){
    return queue -> end == queue -> capacity;
}



int isEmpty(Queue* queue){
    return queue -> start == queue -> end;
}



//adds element to the end of the queue
void enqueue(Queue* queue, int num){
    //if queue not full, we can procede with adding something
    if(isFull(queue)){
        printf("Can't add item to the queue. It is full.\n");
    }else{
        //add the number to the next free position in the array
        int* queueArray = queue -> array;
        queueArray[queue->end] = num;
        //update the size and the end of the queue
        ++(queue -> end);
    }

}



//removes element from the front of the queue
void dequeue(Queue* queue){
    int* queueArr = queue -> array;
    //if queue empty, we can't remove anything
    if(isEmpty(queue)){
        printf("There is nothing in the queue to remove.\n");
    }else{
        for(int i = 0; i < queue -> capacity - 1; i++){
            queueArr[i] = queueArr[i + 1];
        } 
        //overwrite the last element with 0
        queueArr[queue -> end] = 0; 
        --(queue -> end);
    }
}



int peek(Queue* queue){
    int* queueArr = queue -> array; 
    return queueArr[queue -> start]; 
}



void printQueue(Queue* queue){

    if(isEmpty(queue)){
        printf("Queue is empty.\n");
    }else{
        int* array = queue -> array; 
        for(int i = 0; i < queue -> end; i++){
            printf("%d\t", array[i]);
        }
        printf("\n");
    }

}



int main(){

    //create a queue
    Queue* queue = createQueue(100);

    //should be empty
    printQueue(queue);

    //enqueue a few items
    enqueue(queue, 5);
    enqueue(queue, 8);
    enqueue(queue, 0);
    enqueue(queue, 2);
    enqueue(queue, 4);
    //print
    printQueue(queue);

    //dequeue
    dequeue(queue);
    //print
    printQueue(queue);
    //dequeue
    dequeue(queue);
    //print
    printQueue(queue);

    //peek
    printf("Top item in the queue: %d\n", peek(queue));

    //check if empty or full
    printf("Queue empty? %d\n", isEmpty(queue));
    printf("Queue full? %d\n", isFull(queue));

    return 0; 
}
