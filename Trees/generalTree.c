/* Program to implement a tree data structure in which each child has an arbitrary number of nodes */

#include "../queues/fifo.h"

typedef struct Node {

    Node* leftmostChild;
    Node* nextSibling;
    int data;

} Node;



Node* createNode(int data){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode -> data = data;
    newNode ->leftmostChild = NULL;
    newNode ->nextSibling = NULL;
}



void addChild(Node* parent, Node* newChild){
    Node* rightmostChild = parent -> leftmostChild;

    //chase pointers down to rightmost child
    while(rightmostChild -> nextSibling != NULL){
        rightmostChild = rightmostChild -> nextSibling;
    }

    //once we exit the loop, we found the last child in the list. Now append the new child
    rightmostChild -> nextSibling = newChild;
}


enqueueChildren(Queue* queue, Node* parent){
    Node* child = parent -> leftmostChild;
    while(child -> nextSibling != NULL){
        
    }
}



void printTreeLevelOrder(Node* parent){

    Queue* queue = createQueue(100);
    //push the root data
    enqueue(queue, parent -> data);

    //As long as the queue isn't empty
    while(!isEmpty(queue)){

    }

    //push all of the children of parent into the queue
    //print parent and pop


        
}