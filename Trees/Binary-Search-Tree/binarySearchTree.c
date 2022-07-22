#include "binarySearchTree.h"
#include "../General-Tree/treeUtils.h"

Node* initializeNode(int key, Node* parent){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode -> key = key; 
    newNode -> leftChild = NULL;
    newNode -> rightChild = NULL; 
    newNode -> parent = parent; 
}



Node* insertNode(int key, Node* current, Node* parent){

    if(current == NULL){
        //if we hit a null pointer, return the node
        return initializeNode(key, current); 
    }else if(key < current -> key){
        //if the node is less than the parent, we need to explore the left subtree
        current -> leftChild = insertNode(key, current -> leftChild, current);
    }else{
        //if the node is greater, we need to explore the right subtree (node: this implementation assumes no duplicates)
        current -> rightChild = insertNode(key, current -> rightChild, current);
    }

    return current;
}



void deleteNode(Node* root, int key){
    //search for the node to be deleted; store in a variable
    Node* currentNode;
    //store the node's parent in a variable
    Node* parent;
    //case 1: deleting a leaf node
    if(!(currentNode -> rightChild) && !(currentNode -> leftChild)){

        //check if the node to be deleted is the root. If not, the node has a parent whose pointers need fixing
        if(currentNode != root){
            if(parent->leftChild == currentNode){
                parent -> leftChild = NULL;
            }else{
                parent -> rightChild = NULL;
            }
        } else{
            //else the node doesn't have a parent, so just set it to null
            root = NULL;
        }
        //finally, free the node's memory
        free(currentNode);
    } else if(currentNode -> rightChild && currentNode -> leftChild){
        //find the sucessor
        Node* successor = findSuccessor(currentNode, root);
        //store the value of the successor in a variable
        int value = successor -> key;
        //delete the successor (recursively)
        deleteNode(root, successor->key);
        //set the value of successor to the currentNode (recycle the node struct)
        currentNode -> key = value; 
    }else{
        //the current node only has one child; find and store it
        Node* child; 
        if(currentNode -> leftChild){
            child = currentNode -> leftChild;
        }else{
            child = currentNode -> rightChild;
        }

        //if the node isn't a root, it has a parent whose pointers must be fixed
        if(currentNode != root){
            //check if the node is a left child or a right child with respect to its parent
            if(parent->leftChild == currentNode){
                //stitch accordingly
                parent -> leftChild = child;
            }else{
                parent -> rightChild = child;
            }
        }else{
            root = child;
        }
        free(currentNode);
    }
}



Node* findSuccessor(Node* node, Node* root){
    Node* successor;
    if(node -> rightChild){
        successor = findMinimum(node->rightChild);
    }else{
        Node* parent = node -> parent; 
        while(parent && parent -> rightChild == node){
            node = parent;
        }
        successor = node -> parent;
    }
    return successor;
}



Node* findPredecessor(Node* node, Node* root){
    Node* predecessor;
    if(node -> leftChild){
        predecessor = findMaximum(node->leftChild);
    }else{
        Node* parent = node -> parent; 
        while(parent && parent -> leftChild == node){
            node = parent;
        }
        predecessor = node -> parent;
    }
    return predecessor;
}



Node* findMinimum(Node* root){
    Node* currentNode = root;
    while(currentNode -> leftChild){
        currentNode = currentNode -> leftChild;
    }
    return currentNode;
}



Node* findMaximum(Node* root){
    Node* currentNode = root;
    while(currentNode -> rightChild){
        currentNode = currentNode -> rightChild;
    }
    return currentNode;
}



Node* search(int key, Node* root){
    if(root == NULL || key == root -> key){
        return root;
    }else if(key < root -> key){
        return search(key, root -> leftChild);
    }else{
        return search(key, root -> rightChild);
    }
}



void printTreeInorder(Node* root){
    if(root == NULL){
        return;
    }
    printTreeInorder(root -> leftChild);
    printf(root -> key + "\t"); 
    printTreeInorder(root-> rightChild);
}



void enqueueChildren(Queue* queue, Node* parent){
    if(parent -> leftChild){
        enqueue(queue, parent -> leftChild);
    }

    if(parent -> rightChild){
        enqueue(queue, parent -> rightChild);
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
        printf("%d\t", peek(queue) -> key);
        //remove the parent
        dequeue(queue);
        parent = peek(queue);

    }
    printf("\n");
        
}