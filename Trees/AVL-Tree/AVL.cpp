//****************************************************************************************************
// File Name:   AVL.cpp
// Purpose:     AVL tree with operations; originally programmed for CSC 3102, modified August 2022
// Creation Date:        10/17/2020
// Author:      Karley Waguespack
//*****************************************************************************************************

#include <iostream>
#include <stdlib.h>
#include <stddef.h>
#include <fstream>

using namespace std;

//NODE DATA TYPE
typedef struct _Node {

    int key; 
    int data; 
    _Node *left; 
    _Node *right;
    _Node *parent;
    int size; //The number of nodes in total in all subtrees, plus this node itself
    int height; //The longest path down to a leaf node, from this node.
    int mindata; //The minimum data in this node's subtree

} Node;

//GLOBAL VARIABLES
Node *root; //this will hold the root of the AVL tree at any given time; it has to be initialized appropriately using createNode




//creates a new node and initializes all of the values
Node *CreateNode(int key, int data){

    Node *p = NULL;
    p = (Node *) malloc(sizeof(Node));

    p -> key = key; p -> data = data;
    p -> size = 1; p -> height = 1; 
    p -> left = NULL; p -> right = NULL; p -> parent = NULL;
    p -> mindata = data;

    return p;

}



//recalculates the height for a given node
void Recalc_height(Node* x){

    if ((x -> left == NULL) && (x -> right == NULL)){
        //if both left and right pointers are null, the height is composed of only the node itself
        x -> height = 1; 
    } else if (x -> left == NULL){
        x -> height = (x -> right -> height) + 1;
    } else if (x -> right == NULL){
        x -> height = (x -> left -> height) + 1; 
    } else{
        int maxheight = x -> left -> height;
        if (maxheight < x -> right -> height){
            maxheight = x -> right -> height;
        }
        x -> height = 1 + maxheight;
    }
}



//recalculates size for a node 
void Recalc_size(Node *x){
    if ((x -> left == NULL) && (x -> right == NULL)){
        x -> size = 1; 
    } else if (x -> left == NULL){ 
        x -> size = x -> right -> size + 1; 
    } else if (x-> right == NULL){
        x -> size = x -> left -> size + 1; 
    } else {
        x -> size = (x -> left -> size) + (x -> right -> size) + 1; 
    }
}



//recalculates mindata for one node
void Recalc_mindata(Node *x){

    if (!(x -> left) && !(x -> right)){
        x -> mindata = x -> data;
    }else if(!(x -> left)){
        x -> mindata = (x -> right -> mindata < x -> data) ? x -> right -> mindata : x -> data;
    }else if(!(x -> right)){
        x -> mindata = (x-> left -> mindata < x -> data) ? x -> left -> mindata : x -> data; 
    }else{
        int min = x -> data; 
        if (x -> left -> mindata < min){
            min = x -> left -> mindata; 
        }
        if (x -> right -> mindata < min){
            min = x -> right -> mindata; 
        }
    }

}



//left rotates the input node and returns the new node (y) so we can use it in hybrid cases
Node *L_rotate(Node *x){

    Node *p = x -> parent; 
    Node *y = x -> right; 
    Node *z = y -> left; 
    //y becomes parent of x and x becomes left child of y
    y -> left = x; 
    x -> parent = y; 
    //z becomes the right child of x and x becomes parent of z, if it exists
    if(z != NULL){
        x -> right = z; 
        z -> parent = x;
    }else{
        x -> right = NULL;
    }
    //fix the parent so that it points to y instead of x
    if(p != NULL){
        if(p -> left == x){
            p -> left = y; 
            y-> parent = p;
        }else{
            p -> right = y; 
            y -> parent = p;
        }
    } else {
        //this means y is the new root; x was the root previously
        y -> parent = NULL;
        root = y; 
    }
    //fix the height, size, and mindata of the nodes affected
    Recalc_height(x);
    Recalc_height(y);
    Recalc_size(x);
    Recalc_size(y);
    Recalc_mindata(x);
    Recalc_mindata(y);

    return y;
}



//right rotates the input node and returns the new node so we can use it later 
Node *R_rotate(Node *x){

    Node *p = x -> parent; 
    Node *y = x -> left; 
    Node *z = y -> right; 
    //x becomes right child of y; y becomes paren of x 
    y -> right = x; 
    x -> parent = y;
    //z becomes the left child of x and x becomes the parent of z, if it exists
    if(z != NULL){
        x -> left = z; 
        z -> parent = x;
    }else{
        x -> left = NULL;
    }
    //If x had a parent previously, we have to stitch it to y
    if(p != NULL){
        if(p -> left == x){
            p -> left = y; 
            y-> parent = p;
        }
        if(p -> right == x){
            p -> right = y; 
            y -> parent = p;
        }
    } else {
        //if not, that means x was previously the root, so y is the new root
        y -> parent = NULL;
        root = y;  
    }
    //fix height, size, and mindata for all nodes affected
    Recalc_height(x);
    Recalc_height(y);
    Recalc_size(x);
    Recalc_size(y);
    Recalc_mindata(x);
    Recalc_mindata(y);

    return y;

}


//Left rotates a node then right rotates it; will be used in a zig zag case [<] 
Node *LR_rotate(Node *x){
    L_rotate(x -> left);
    Node* node = R_rotate(x);
    return node;
}



//Right rotates a node then left rotates it; will be used in a zig zag case [>] 
Node *RL_rotate(Node *x){
    R_rotate(x -> right);
    Node* node = L_rotate(x);
    return node; 
}



//calculates the bf of a node
int CalculateBF(Node *x){
    int rightHeight;
    if(x -> right == NULL){
        rightHeight = 1; 
    }else{
        rightHeight = (x -> right -> height) +1;
    }

    int leftHeight; 
    if(x -> left == NULL){
        leftHeight = 1; 
    }else{
        leftHeight = (x -> left -> height) + 1;
    }

    int BF = leftHeight - rightHeight;
    return BF;
}



//when calling, current is initialized to root
Node* Insert(Node *current, int insertedKey, int insertedData){

    //PERFORM NORMAL BST INSERTION RECURSIVELY
    if(current == NULL){
        //if we hit a null pointer, return the node
        return CreateNode(insertedKey, insertedData);
    }else if(insertedKey < current -> key){
        //if the node is less than the parent, we need to explore the left subtree
        current -> left = Insert(current -> left, insertedKey, insertedData);
    }else{
        //if the node is greater, we need to explore the right subtree (node: this implementation assumes no duplicates)
        current -> right = Insert(current -> right, insertedKey, insertedData);
    }

    /*** NOTE: the following lines will complete in a bottom-up manner for all nodes in the insertion path, once recursion stops ***/

    //FIX VALUES FOR EACH NODE IN THE INSERTION PATH
    Recalc_height(current);
    Recalc_size(current);
    Recalc_mindata(current);

    //FIND FIRST UNBALANCED NODE AND FIX THE TREE: 
    int currentBalanceFactor = CalculateBF(current);
    //left left case -> "/"
    if(currentBalanceFactor > 1 && insertedKey > current -> left -> key){
        return R_rotate(current);
    }
    //left right case -> "<"
    if(currentBalanceFactor > 1 && insertedKey < current -> left -> key){
        return LR_rotate(current);
    }
    //right right case -> "\"
    if(currentBalanceFactor < -1 && insertedKey < current -> right -> key){
        return L_rotate(current);
    }
    //right left case -> ">"
    if(currentBalanceFactor < -1 && insertedKey > current -> right -> key){
        return RL_rotate(current);
    }
    
    return current;

}



//implement delete
Node* Delete(Node* currentNode, int key){

    //PERFORM NORMAL BST DELETE
    if(root == NULL){
        return currentNode;
    }
    if(key < currentNode -> key){
        return Delete(currentNode -> left, key);
    } else if(key > currentNode -> key){
        return Delete(currentNode -> right, key);
    }
    else{
        //root is node to be deleted
        Node* parent = currentNode -> parent;
        //case 1: deleting a leaf node
        if(!(currentNode -> right) && !(currentNode -> left)){

            //check if the node to be deleted is the root. If not, the node has a parent whose pointers need fixing
            if(currentNode != root){
                if(parent->left == currentNode){
                    parent -> left = NULL;
                }else{
                    parent -> right = NULL;
                }
            } else{
                //else the node doesn't have a parent, so just set it to null
                root = NULL;
            }
            //finally, free the node's memory
            free(currentNode);
            

        } else if(currentNode -> right && currentNode -> left){
            //find the sucessor
            Node* successor = FindSuccessor(currentNode->key, root);
            //store the value of the successor in a variable
            int value = successor -> key;
            //delete the successor (recursively)
            Delete(root, successor->key);
            //set the value of successor to the currentNode (recycle the node struct)
            currentNode -> key = value; 
        }else{
            //the current node only has one child; find and store it
            Node* child; 
            if(currentNode -> left){
                child = currentNode -> left;
            }else{
                child = currentNode -> right;
            }

            //if the node isn't a root, it has a parent whose pointers must be fixed
            if(currentNode != root){
                //check if the node is a left child or a right child with respect to its parent
                if(parent->left == currentNode){
                    //stitch accordingly
                    parent -> left = child;
                }else{
                    parent -> right = child;
                }
            }else{
                root = child;
            }
            free(currentNode);
        }

    }


}



//search is the same as normal BST searching
Node* Search(int key, Node* root){
    if(root == NULL || key == root -> key){
        return root;
    }else if(key < root -> key){
        return Search(key, root -> left);
    }else{
        return Search(key, root -> right);
    }
}



Node* FindSuccessor(int key, Node* root){
    Node* node = Search(key, root);
    Node* successor;
    //if the node has a right child, just find the minimum of this subtree
    if(node -> right){
        successor = FindMinimum(node->right);
    }else{
        //otherwise, find the first right ancestor
        Node* parent = node -> parent; 
        while(parent && parent -> right == node){
            node = parent;
        }
        successor = node -> parent;
    }
    return successor;
}



Node* FindMinimum(Node* root){
    Node* currentNode = root;
    while(currentNode -> left){
        currentNode = currentNode -> left;
    }
    return currentNode;
}



//implement level order printing
void PrintTreeLevelOrder(){

}



//finds the least common ancestor given two keys, k1 and k2
Node *LCA(int k1, int k2, Node *x){
    if(k1 < x -> key && k2 < x -> key){
        x = x -> left;
        return LCA(k1, k2, x);
    } else if(k1 > x -> key && k2 > x -> key){
        x = x -> right;
        return LCA(k1, k2, x);
    } else{
        return x;
    }
}



//finds the minimum in a list of numbers
int FindMin(int *array, int n){
    int min = array[0];
    for(int i = 1; i<n; i++){
        if(array[i] < min){
            min = array[i];
        }
    }
    return min;
}



//finds the minimum element within the range k1 and k2 in the tree
int RangeMinimum(int k1, int k2, Node *y){

    int maxSize = 100;
    //create a dynamic array for storing the mindata
    int n = 0; //n is the current size of the array
    int *minList = (int *) malloc(100 * sizeof(int));

    //find the least common ancsetor 
    Node *ancestor = LCA(k1, k2, y);
    n++; 
    minList[n-1] = ancestor -> data;

    Node *x;
    if(ancestor -> left != NULL){
        x = ancestor -> left;
        if(x -> key == k1 && x -> right != NULL){
            n++;
            minList[n-1] = x -> right -> mindata;
        }
        
        while(x != NULL && x -> key != k1){
            if(x -> key >= k1){
                n++;
                minList[n-1] = x -> data;
                if(x -> right != NULL){
                    n++;
                    minList[n-1] = x -> right -> mindata; 
                }
                x = x -> left;
            } else{
                x = x -> right;
            }
        }
    }

    
    //k2 path
    if(ancestor -> right != NULL){
        x = ancestor -> right;
        if(x -> key == k2 && x -> left != NULL){
            n++;
            minList[n-1] = x -> left -> mindata;
        }

        while(x != NULL && x -> key != k2){
            if(x -> key <= k2){
                n++;
                minList[n-1] = x -> data;
                if(x -> left != NULL){
                    n++;
                    minList[n-1] = x -> left -> mindata; 
                }
                x = x -> right;
            } else{
                x = x -> left;
            }
        }
    }

    return FindMin(minList, n);

}



//driver code
int main(int argc, char *argv[]){

    //get the argument; assumed to be entered as a string
    string inputFile = argv[1];
    //open a file
    ifstream file(inputFile);
    //create variables for arguments
    string instruction;
    int arg1;
    int arg2;
    int counter = 0;
    int min;

    //read line by line
    while(file >> instruction >> arg1 >> arg2){

        if(instruction == "IN"){
            ++counter;
            //if we're making the first insertion, create the root node
            if(counter == 1){
                root = CreateNode(arg1, arg2);
            }
            //otherwise, insert a node.
            else{
                Insert(root, arg1, arg2);
            }
        } else if(instruction == "RM"){
            min = RangeMinimum(arg1, arg2, root);  
            printf("Found minimum: %d\n", min);
        }
    }

    return 0;


}