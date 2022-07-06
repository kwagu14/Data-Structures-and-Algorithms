/* Program to implement a tree data structure in which each child has an arbitrary number of nodes */

#include "utils.h"


GeneralNode* createGeneralNode(int data){
    GeneralNode* newNode = (GeneralNode*) malloc(sizeof(GeneralNode));
    newNode -> data = data;
    newNode -> leftmostChild = NULL;
    newNode -> nextSibling = NULL;
    return newNode;
}



void addChild(GeneralNode* parent, GeneralNode* newChild){

    if(parent -> leftmostChild){

        GeneralNode* rightmostChild = parent -> leftmostChild;
        //chase pointers down to rightmost child
        while(rightmostChild -> nextSibling != NULL){
            rightmostChild = rightmostChild -> nextSibling;
        }
        //once we exit the loop, we found the last child in the list. Now append the new child
        rightmostChild -> nextSibling = newChild;

    }else{
        //the parent has no children, so just set the leftmost child pointer
        parent -> leftmostChild = newChild;
    }
}



//enqueues all of the node's children
void enqueueChildren(Queue* queue, GeneralNode* parent){
    if(!(parent -> leftmostChild)){
        return;
    }else{
        //get and enqueue the first child 
        GeneralNode* child = parent -> leftmostChild;
        enqueue(queue, child);
        while(child -> nextSibling){
            child = child -> nextSibling;
            enqueue(queue, child);
        }
    }   
}



//prints the data in level order as a stream (no newlines)
void printTreeLevelOrder(GeneralNode* parent){

    printf("Printing out the tree in level-order: \n");
    Queue* queue = createQueue(100);
    //push the root
    enqueue(queue, parent);

    //As long as the queue isn't empty
    while(!isEmpty(queue)){
        //push the parent's children into the queue
        enqueueChildren(queue, parent);
        //print the parent's data
        printf("%d\t", peek(queue) -> data);
        //remove the parent
        dequeue(queue);

        if(parent -> nextSibling == NULL){
            //if no next sibling, use the next node in the queue
            parent = peek(queue);
        }else{
            //otherwise use the next sibling
            parent = parent -> nextSibling;
        }

    }
    printf("\n");
        
}



int main(){

    //create the root node 
    GeneralNode* root = createGeneralNode(7);
    //create some children
    GeneralNode* c1 = createGeneralNode(9);
    GeneralNode* c2 = createGeneralNode(5);
    GeneralNode* c3 = createGeneralNode(1);
    GeneralNode* c4 = createGeneralNode(2);
    GeneralNode* c5 = createGeneralNode(4);
    GeneralNode* c6 = createGeneralNode(6);
    GeneralNode* c7 = createGeneralNode(3);
    GeneralNode* c8 = createGeneralNode(1);
    GeneralNode* c9 = createGeneralNode(7);
    GeneralNode* c10 = createGeneralNode(0);
    
    //append them
    addChild(root,c1);  //9
    addChild(root, c2); //5
    addChild(root, c3); //1
    addChild(c1, c4);   //2
    addChild(c1, c5);   //4
    addChild(c3, c6);   //6
    addChild(c3, c7);   //3
    addChild(c3, c8);   //1
    addChild(c4, c9);   //7
    addChild(c6, c10);  //0

    //print levelorder 
    printTreeLevelOrder(root);



    return 0; 
}