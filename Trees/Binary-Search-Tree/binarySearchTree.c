#include "binarySearchTree.h"


int main(){


    //create a node to function as the root of the tree
    Node* root = initializeNode(8, NULL);
    //build the tree
    insertNode(6, root, NULL);
    insertNode(10, root, NULL);
    insertNode(1, root, NULL);
    insertNode(7, root, NULL); 
    insertNode(9, root, NULL);
    insertNode(12, root, NULL);

    //print the tree (inorder): 1, 6, 7, 8, 9, 10, 12
    printf("printing out the tree in order:\n");
    printTreeInorder(root);
    printf("\n");
    //print the tree (level order): 8, 6, 10, 1, 7, 9, 12 
    printTreeLevelOrder(root);

    //search for key 7:
    printf("key of found node: %d\n", search(7, root)->key);
    //minimum: 1
    printf("Minimum of the tree: %d\n", findMinimum(root)->key);
    //maximum: 12
    printf("Maximum of the tree: %d\n", findMaximum(root)->key);
    //successor of 8: 9
    printf("successor of 8 is %d\n", findSuccessor(8, root)->key);
    //predecessor of 9: 8
    printf("predecessor of 9 is %d\n", findPredecessor(9, root)->key);

    deleteNode(root, 8);
    //9, 6, 10, 1, 7, 12
    printTreeLevelOrder(root);
    deleteNode(root, 10);
    //9, 6, 12, 1, 7
    printTreeLevelOrder(root);
    deleteNode(root, 1); 
    //9, 6, 12, 7
    printTreeLevelOrder(root);

    return 0; 
}



Node* initializeNode(int key, Node* parent){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode -> key = key; 
    newNode -> leftChild = NULL;
    newNode -> rightChild = NULL; 
    newNode -> parent = parent; 
}


//when calling, current is initialized to root and parent is null
Node* insertNode(int key, Node* current, Node* parent){

    if(current == NULL){
        //if we hit a null pointer, return the node
        return initializeNode(key, parent); 
    }else if(key < current -> key){
        //if the node is less than the parent, we need to explore the left subtree
        parent = current;
        current -> leftChild = insertNode(key, current -> leftChild, parent);
    }else{
        //if the node is greater, we need to explore the right subtree (node: this implementation assumes no duplicates)
        parent = current;
        current -> rightChild = insertNode(key, current -> rightChild, parent);
    }

    return current;
}



void deleteNode(Node* root, int key){
    //search for the node to be deleted; store in a variable
    Node* currentNode = search(key, root);
    //store the node's parent in a variable
    Node* parent = currentNode -> parent;
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
        Node* successor = findSuccessor(currentNode->key, root);
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



Node* findSuccessor(int key, Node* root){
    Node* node = search(key, root);
    Node* successor;
    //if the node has a right child, just find the minimum of this subtree
    if(node -> rightChild){
        successor = findMinimum(node->rightChild);
    }else{
        //otherwise, find the first right ancestor
        Node* parent = node -> parent; 
        while(parent && parent -> rightChild == node){
            node = parent;
        }
        successor = node -> parent;
    }
    return successor;
}



Node* findPredecessor(int key, Node* root){
    Node* node = search(key, root);
    Node* predecessor;
    //if the node has a left child, just find the maximum of this subtree
    if(node -> leftChild){
        predecessor = findMaximum(node->leftChild);
    }else{
        //otherwise, find the first left ancestor
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
    printf("%d\t", root -> key); 
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


Queue* createQueue(int capacity){
    Queue* queue = (Queue*) malloc(sizeof(Queue)); 
    //set all of the properties for bookkeeping 
    queue -> capacity = capacity; 
    queue -> start = 0; 
    queue -> end = 0; 
    //create an array of the correct size
    queue -> array = (Node**) malloc(capacity * sizeof(Node*));
    return queue;
}



int isFull(Queue* queue){
    return queue -> end == queue -> capacity;
}



int isEmpty(Queue* queue){
    return queue -> start == queue -> end;
}



//adds element to the end of the queue
void enqueue(Queue* queue, Node* node){
    //if queue not full, we can procede with adding something
    if(isFull(queue)){
        printf("Can't add item to the queue. It is full.\n");
    }else{
        //add the number to the next free position in the array
        Node** queueArray = queue -> array;
        queueArray[queue->end] = node;
        //update the size and the end of the queue
        ++(queue -> end);
    }

}



//removes element from the front of the queue
void dequeue(Queue* queue){
    Node** queueArr = queue -> array;
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



Node* peek(Queue* queue){
    Node** queueArr = queue -> array; 
    return queueArr[queue -> start]; 
}