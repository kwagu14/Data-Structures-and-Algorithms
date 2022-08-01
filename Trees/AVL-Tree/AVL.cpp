//****************************************************************************************************
// File Name:   AVL.cpp
// Purpose:     AVL tree with insert and range minimum operations; CSC 3102 / Dr. Rahul Shah
// Date:        10/17/2020
// Author:      Karley Waguespack (kwagu14)
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
    int size; //should be the number of nodes in total in all subtrees, plus this node itself
    int height; //should be the longest path down to a leaf node, from this node.
    int mindata; //should be the minimum data in this node's subtree

} Node;



//GLOBAL VARIABLES
Node *root; //this will hold the root of the avl tree at any given time; it has to be initialized appropriately using createNode
bool heightIncreased = false; //will flag if height changed



//creates a new node and initializes all of the values
Node *createNode(int _key, int _data){

    Node *p = NULL;
    p = (Node *) malloc(sizeof(Node));

    p -> key = _key; p -> data = _data;
    p -> size = 1; p -> height = 1; 
    p -> left = NULL; p -> right = NULL; p -> parent = NULL;
    p -> mindata = _data;

    return p;

}



//HELPER FUNCTIONS

//this should be called on every node 
//from bottom up
void recalc_height(Node* x){

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



//recalculates size for each node; should be called on node inserted as well
//as all of the ancestors from bottom up. 
void recalc_size(Node *x){
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



//recalculates mindata for one node; after inserting, this should be recalculated for the 
//node inserted as well as all of its ancestors from bottom up
void recalc_mindata(Node *x){

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



//left rotates the input node and returns the new node so we can use it in hybrid cases
//this will be used in a zig zig case [\]
Node *l_rotate(Node *x){


    Node *p = x -> parent; 
    Node *y = x -> right; 
    Node *z = y -> left; 

    //perform rotation
    y -> left = x; x -> parent = y; 
    if(z != NULL){
        x -> right = z; z -> parent = x;
    }else{
        x -> right = NULL;
    }

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
        y -> parent = NULL;
        root = y; 
    }

    recalc_height(x);
    recalc_height(y);
    recalc_size(x);
    recalc_size(y);
    recalc_mindata(x);
    recalc_mindata(y);

    return y;
}



//right rotates the input node and returns the new node so we can use it later 
//this will be used in a zig zig case of rotation [/]
Node *r_rotate(Node *x){

    Node *p = x -> parent; 
    Node *y = x -> left; 
    Node *z = y -> right; 

    //perform the rotation 
    y -> right = x; x -> parent = y;
    if(z != NULL){
        x -> left = z; z -> parent = x;
    }else{
        x -> left = NULL;
    }

    //fix the top part of the tree
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
        y -> parent = NULL;
        root = y;  
    }

    recalc_height(x);
    recalc_height(y);
    recalc_size(x);
    recalc_size(y);
    recalc_mindata(x);
    recalc_mindata(y);

    return y;

}

//Left rotates a node then right rotates it; will be used in a zig zag case [<] 
Node *LR_rotate(Node *x){
    l_rotate(x -> left);
    Node* node = r_rotate(x);

    return node;
}



//Right rotates a node then left rotates it; will be used in a zig zag case [>] 
Node *RL_rotate(Node *x){
    r_rotate(x -> right);
    Node* node = l_rotate(x);

    return node; 
}



//calculates the bf of a node
int calculateBF(Node *x){
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



//takes a node created by the createNode function and places it in the right spot in the tree. 
//also takes in the root node; must be created beforehand
void Insert(Node *x, Node *z){

    //if the key to be inserted is greater than root, then we need to insert it in the right
    if(x -> key < z -> key){
        if(x -> right){
            Insert(x -> right, z);
            recalc_height(x);
            recalc_height(x);
            recalc_mindata(x);
            recalc_size(x);
        }else{
            //set the right child to z; set z's parent to x ***
            x -> right = z; z -> parent = x;
            heightIncreased = true; 
            recalc_height(z);
            recalc_height(x);
            recalc_mindata(z);
            recalc_mindata(x);
            recalc_size(z);
            recalc_size(x);
            
        } 
        if(heightIncreased){

            //calculate right height 
            int xBF = calculateBF(x);

            //case 2.1 and case 2.2: no need to do any rotation 
            if(xBF == 0){
                heightIncreased = false;
            }
        
            //case 2.3: this is if bf was previously -1 but is now -2
            else if (xBF == -2){

                int xrBF = calculateBF(x -> right);

                //subcase 1: if the right balance factor is -1
                if(xrBF == - 1){

                    l_rotate(x); //zig zig case [\]; be sure to update to the new root

                    heightIncreased = false;
                }
                //subcase 2: if the right subtree balance factor is 1
                else if (xrBF == 1) {
                    int xrlBF = calculateBF(x -> right -> left);
                    RL_rotate(x);
                    if(xrBF == -1){
                        heightIncreased = false; 
                    }
                    
                }
            }
        } 
    }
    //otherwise, if the key is smaller than the root, then we need to insert it in the left
    else{
        if(x -> left){
            Insert(x -> left, z);
            recalc_height(x);
            recalc_mindata(x);
            recalc_size(x);
        
        }else{
            //set the right child to z
            x -> left = z; z -> parent = x;
            heightIncreased = true; 
            recalc_height(z);
            recalc_height(x);
            recalc_mindata(z);
            recalc_mindata(x);
            recalc_size(z);
            recalc_size(x);

        } 
        if(heightIncreased){
            //calculate the left height
            int xBF = calculateBF(x);

            //case 2.1 and 2.2: no need to do any rotation
            if(xBF == 0){
                bool xBF = 0;
                heightIncreased = false;
            }
            
            //case 2.3: this is if bf was previously 1 but is now 2
            else if(xBF == 2){
                bool xBF = 2; 
                int xlBF = calculateBF(x -> left);

                //subcase 1: if the right balance factor is 1
                if(xlBF == 1){
                    r_rotate(x); //zig zig case [/]; be sure to update root to new root
                    heightIncreased = false;
                    //no need to fix height for this case
                }
                //subcase 2: 
                else if (xlBF == -1) {
                    int xlrBF = calculateBF(x -> left -> right);
                    LR_rotate(x);
                    if(xlrBF == 1){
                        heightIncreased = false; 
                    }
                    
                    
                }
                    
                
            }
        } 
    }
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
int findMin(int *array, int n){
    int min = array[0];
    for(int i = 1; i<n; i++){
        if(array[i] < min){
            min = array[i];
        }
    }
    return min;
}



int RangeMinimum(int k1, int k2, Node *y){

    //create a dynamic array for storing the mindata
    int n = 0; //n is the current size of the array
    int *minList = (int *) malloc(n * sizeof(int));

    //find the least common ancsetor and call it x
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

    return findMin(minList, n);

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
            counter ++;
            //if we're making the first insertion, create the root node
            if(counter == 1){
                root = createNode(arg1, arg2);
            }
            //otherwise, insert a node.
            else{
                Insert(root, createNode(arg1, arg2));
            }
        } else{
            min = RangeMinimum(arg1, arg2, root);  
        }
    }
    printf("%d\n", min);

    return 0;


}