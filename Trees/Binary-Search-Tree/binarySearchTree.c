/* 
    PRINTING
        print level order
        print inorder

    QUERY OPERATIONS
        find minimum
        find maximum
        find sucessor
        find predecessor
        search
    
    MODIFICATION OPERATIONS
        insert node
        delete node

    TREE IMPLEMENTATION
        The tree will be implemented with node structs bound together by pointers. 
        Since the tree is not guaranteed to be perfectly balanced, implementing it using an array is not feasible

*/

#include "binarySearchTree.h"

Node* initializeNode(int key){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode -> key = key; 
    newNode -> leftChild = NULL;
    newNode -> rightChild = NULL; 
    newNode -> parent = NULL; 
}



void freeNode(Node* node){

}



Node* insertNode(int key, Node* root){
    //NEED TO FIGURE OUT HOW TO SET PARENT POINTER
    
    if(root == NULL){
        //if we hit a null pointer, return the node
        return initializeNode(key); 
    }else if(key < root -> key){
        //if the node is less than the parent, we need to explore the left subtree
        root-> leftChild = insertNode(key, root -> leftChild);
    }else{
        //if the node is greater, we need to explore the right subtree (node: this implementation assumes no duplicates)
        root -> rightChild = insertNode(key, root -> rightChild);
    }

    return root;
}



void deleteNode(Node* root, int key){
    //search for the node to be deleted; store in a variable
    Node* currentNode;
    //store the node's parent in a variable
    Node* parent;
    //case 1: deleting a leaf node
    if(!(currentNode -> rightChild) && !(currentNode -> leftChild)){
        //FREE THE NODE MEMORY

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
    }
}
