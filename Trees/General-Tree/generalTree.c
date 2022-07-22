/* Program to implement a tree data structure in which each child has an arbitrary number of nodes */

#include "treeUtils.h"


Node* createNode(int data){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode -> data = data;
    newNode -> leftmostChild = NULL;
    newNode -> nextSibling = NULL;
    return newNode;
}



void addChild(Node* parent, Node* newChild){

    if(parent -> leftmostChild){

        Node* rightmostChild = parent -> leftmostChild;
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



//enqueues all of the children of a given node 
void enqueueChildren(Queue* queue, Node* parent){
    if(!(parent -> leftmostChild)){
        return;
    }else{
        //get and enqueue the first child 
        Node* child = parent -> leftmostChild;
        enqueue(queue, child);
        while(child -> nextSibling){
            child = child -> nextSibling;
            enqueue(queue, child);
        }
    }   
}



//prints the data in level order as a stream (no newlines)
void printTreeLevelOrder(Node* parent){

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
        parent = peek(queue);

    }
    printf("\n");
        
}



int main(){

    //create the root node 
    Node* root = createNode(7);
    //create some children
    Node* c1 = createNode(9);
    Node* c2 = createNode(5);
    Node* c3 = createNode(1);
    Node* c4 = createNode(2);
    Node* c5 = createNode(4);
    Node* c6 = createNode(6);
    Node* c7 = createNode(3);
    Node* c8 = createNode(1);
    Node* c9 = createNode(7);
    Node* c10 = createNode(0);
    
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