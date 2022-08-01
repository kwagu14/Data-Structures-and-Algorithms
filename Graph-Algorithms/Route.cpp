#include <iostream>
#include <stdlib.h>
#include <stddef.h>

#include <iostream>
#include <fstream>
#include <climits>

using namespace std;



//-------------------------------------------TYPE DEFINITIONS-------------------------------------------//

//defines an edge
typedef struct _Edge {
    
    //these two define the end nodes on the edge
    char origin[3]; //origin airport
    char destination[3]; //destination airport

    char airline[2]; 
    int flightNum;

    //these two can be used to maintain the shortest time label
    int departTime; 
    int arriveTime;
    _Edge *next; //this will be used in the adjacency list to tell which element is next

} Edge;


//defines a vertex
typedef struct _Vertex {

    char airportCode[3]; //the code must be a char array
    int heapPos; //index in heap array; depends on what its tvalue is
    int hashPos; //index in hash; found using hash function
    Edge *adjacencyList; //store edges in the adjacency list since opposite vertex is easily determined by 'destination' field
    int tvalue; //will get updated using Dijkstra's; should be initialized to 'infinity' (max int)
    //string parentCode; //this will be the parent in the cloud (shortest time tree)
    _Vertex *parent;
    _Vertex *nextInCloud;
    _Vertex *next; //this will store a pointer to the next vertex in the hash; must be stored as a linked list in case of collision

} Vertex;



//--------------------------------------TYPE CONSTRUCTOR FUNCTIONS-------------------------------//

//creates a new edge
Edge * createEdge(string _airline, int _flightNum, string _origin, string _destination, int _departTime, int _arriveTime) {
    
    Edge *newEdge = NULL;
    newEdge = (Edge *) malloc(sizeof(Edge));

    //converting the strings to char arrays
    newEdge -> airline[0] = _airline[0];
    newEdge -> airline[1] = _airline[1];
    newEdge -> origin[0] = _origin[0];
    newEdge -> origin[1] = _origin[1];
    newEdge -> origin[2] = _origin[2];
    newEdge -> destination[0] = _destination[0];
    newEdge -> destination[1] = _destination[1];
    newEdge -> destination[2] = _destination[2];
 
    newEdge -> flightNum = _flightNum; 
    newEdge -> departTime = _departTime; 
    newEdge -> arriveTime = _arriveTime;

    newEdge -> next = NULL;

    return newEdge;
}



//creates a new vertex
Vertex * createVertex(string code) {
    
    Vertex *newVertex = NULL;
    newVertex = (Vertex *) malloc(sizeof(Vertex));
    newVertex -> airportCode[0] = code[0];
    newVertex -> airportCode[1] = code[1];
    newVertex -> airportCode[2] = code[2];

    newVertex -> heapPos = 0;
    newVertex -> hashPos = 0;
    newVertex -> adjacencyList = NULL;
    newVertex -> tvalue = INT_MAX;
    newVertex -> parent = NULL;
    newVertex -> nextInCloud = NULL;
    newVertex -> next = NULL;

    return newVertex;
}



//-----------------------------------GLOBAL VARIABLES-------------------------------------------//

//hash that will store vertecies; we'll have adjacency lists associated with each vertex
Vertex *hashArray[1000];
//heap array that will store pointers to each vertex in the hash array
Vertex *heapArray[1000];
int heapSize; //maintains the size of the heap



//---------------------------------DATA PROCESSING (BUILDS GRAPH)---------------------------------//

//hash function that will map each vertex to a position in the 1000 element array
int vertexHash (string code){

    int p0 = (int) code[0] - 'A' +1;
    int p1 = (int) code[1] - 'A' +1;
    int p2 = (int) code[2] - 'A' +1;

    int p3 = p0 * 467 * 467 + p1 * 467 + p2;

    int p4 = p3 % 7193;

    return p4 % 1000; //this is the position in the array that a given vertex will occupy, based on its 3-letter code

}



//this function builds the hashArray from the airports.txt file
void buildHashArray(){

    //initialize the arrays so that the default value is null. 
    for(int i = 0; i < 1000; i++){
        hashArray[i] = NULL;
        heapArray[i] = NULL;
    }

    //open airports.txt
    ifstream airports("airports.txt");
    //skip the first line
    int airportTotal;
    airports >> airportTotal;
    //read all of the data and put into variables
    string code;
    int heapPosition = 0;
    while(airports >> code){

        //create the vertices and put them into the arrays
        Vertex *newVertex = createVertex(code);
        
        //heap array; just place the vertices one after the other at the beginning of the array
        heapArray[heapPosition] = newVertex;
        heapSize ++; 
        newVertex -> heapPos = heapPosition;
        heapPosition ++;

        //the hash array
        int pos = vertexHash(code);
        newVertex -> hashPos = pos;

        if(hashArray[pos] == NULL){
            hashArray[pos] = newVertex;
        } else {
            //otherwise, find the end of the linked list
            Vertex *v = hashArray[pos];
            while(v -> next != NULL){
                v = v -> next;
            }
            //the loop will stop when v->next is equal to null; meaning v is the last vertex
            v -> next = newVertex;
        }

    }
    airports.close();
}


//helper function that converts a given char array to a string
string convertToString(char arr[], int size){

    string str = "";
    for(int i = 0; i < size; i++){
        str = str + arr[i]; 
    }
    return str;
    
}



//this function builds the adjacency lists based on data from flights.txt
void buildAdjacencyLists(){
    //go through the flights.txt file line by line; skip the 1st two lines
    ifstream flights("flights.txt");
   
    //skip first two
    string flightCount; 
    string header; 
    getline(flights, flightCount);
    getline(flights, header); 

    //variables to hold the data
    string airline;
    int flightNumber; 
    string origin;
    string destination;
    int departure; 
    int arrival; 
    int distance; 

    //initialize the edges directly
    while(flights >> airline >> flightNumber >> origin >> destination >> departure >> arrival >> distance){
        
        Edge *newEdge = createEdge(airline, flightNumber, origin, destination, departure, arrival);
        Vertex *targetVertex;

        //for the origin vertex, find it's position in the hash
        int pos = vertexHash(origin);
        string codeString = string(hashArray[pos] -> airportCode, 3);

        //it is possible that there is more than one vertex in this position; we need to find the right target
        if(codeString == origin){
            targetVertex = hashArray[pos];
        }else{
            //otherwise, we have a linked list and need to search
            targetVertex = hashArray[pos] -> next;
            codeString = convertToString(targetVertex -> airportCode, 3);
            while(codeString != origin){
                targetVertex = targetVertex -> next;
                codeString = convertToString(targetVertex -> airportCode, 3);
            }
            //once we exit, targetVertex will be the correct value
        }

        //if the adjacency list doesn't have anything attached, set the first edge
        if(targetVertex -> adjacencyList == NULL) {
            targetVertex -> adjacencyList = newEdge; //puts the 1st edge
        } else {
            //otherwise, find the end of the list
            Edge *e = targetVertex -> adjacencyList;
            while(e -> next != NULL){
                e = e -> next;
            }
            //the loop will stop when e -> next is null; this is where newEdge goes
            e -> next = newEdge;

        }

    }
    flights.close();
}


//swaps two elements in an array; takes in the array and the two indices to be swapped.
void swapElements(Vertex *array[], int i, int j){
    Vertex *temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}



//---------------------------------HEAP-------------------------------------------------//

//bubbles down a given vertex to correct position in heap; Note: usually used on absolute root after extractMin
void sinkDown(Vertex *array[], int root){

    //left and right children
    int left = 2*root + 1;
    int right = 2*root + 2;

    //initialize the minimum to be the element
    int min = root;

    //find the actual minimum among parent/children; minimum is based on tvalue
    if(left < heapSize && array[left] -> tvalue < array[min] -> tvalue){
            min = left;
    }	
    if(right < heapSize && array[right] -> tvalue < array[min] -> tvalue){
            min = right;
    }

    //if the min was updated to left or right child
    if(min != root){
            //update the heapPos fields before the swap
            array[min] -> heapPos = root;
            array[root] -> heapPos = min;
            swapElements(array, min, root);
            sinkDown(array, root);
    }
}



//floats up a given vertex to the correct position in the heap; needed for decrease key
//position of the vertex is needed
void floatUp(Vertex *array[], Vertex *v){

    //we need to get the position of v in the heap; this is stored in 'child' variable
    int child = v -> heapPos;

    //note that 'child' is the key we decresased; we need to get it's parent
    int parent = (child - 1)/2;

    //if the parent is still inside the heap and the child's tvalue is less than parent's, we need to fix this
    if(parent >= 0 && array[child] -> tvalue < array[parent] -> tvalue){

        array[child] -> heapPos = parent;
        array[parent] -> heapPos = child;
        swapElements(array, child, parent);
        Vertex *parent_v = array[parent];
        floatUp(array, parent_v);
    }
}



//decreases the tvalue in a certain vertex to a lower value and fixes heap
//position of the vertex is needed
void DecreaseKey(Vertex *array[], Vertex *v, int value){

    int pos = v -> heapPos;
    array[pos] -> tvalue = value; 
    floatUp(array, v);
}



//exctracts the vertex with the smallest tvalue (this will always be at the top of the heap)
Vertex *extractMinimum(Vertex *array[]){

    array[0] -> heapPos = heapSize - 1;
    array[heapSize -1] -> heapPos = 0;
    swapElements(array, 0, heapSize - 1);
    heapSize --; 
    sinkDown(array, 0);
    return array[heapSize];
}



Vertex *getVertex(string code){

    int position = vertexHash(code);
    Vertex *v = hashArray[position];

    if(convertToString(v -> airportCode, 3) == code){
        return v;
    }else{

        v = v -> next;
        while(convertToString(v -> airportCode, 3) != code){
            v = v -> next;
        }
        return v;

    }

}



//-------------------------------PATH FINDING (SHORTEST TIME)------------------------------------//

void relax(Edge *e){

    //retrieve the origin vertex
    string originCode = convertToString(e -> origin, 3);
    Vertex *u = getVertex(originCode);

    //we will only be able to use the flight if it departs after the arrival time 
    if(e -> departTime <= u -> tvalue){
        return;
    }

    //retrieve the destination
    string destinationCode = convertToString(e -> destination, 3);
    Vertex *z = getVertex(destinationCode);

    //if the best time for the child is greater than the new arrival time, we need to update it to the shorter time
    if(z -> tvalue > e -> arriveTime){
        //we need to decrease the key
        DecreaseKey(heapArray, z, e -> arriveTime);
        //immediately after updating, set the parent 
        z -> parent = u;
    }

}



//finds the shortest path; 
void Dijkstra(Vertex *source){

    //decrease the t-value of the source vertex to 0
    DecreaseKey(heapArray, source, 0);
    //if the heap isn't empty, then we have some vertex that hasn't been processed
    while(heapSize > 0){
        //this statment will grab the minimum and remove it from the heap
        Vertex *v = extractMinimum(heapArray);
        //relax all of the edges from v
        Edge *currentEdge = v -> adjacencyList;
        while(currentEdge != NULL){
            relax(currentEdge);
            currentEdge = currentEdge -> next;
        }

    }

}



//outputs the shortest time given a starting and ending airport
void findQuickestPath(string start, string end){

    Vertex *currentAirport = getVertex(end);
    Vertex *parentAirport = currentAirport -> parent; 

    while(parentAirport != NULL){
        parentAirport -> nextInCloud = currentAirport;
        currentAirport = currentAirport -> parent;
        parentAirport = currentAirport -> parent;
    }

    //start node is the starting node in the stack
    Vertex *nextAirport = getVertex(start);

   while(nextAirport != NULL){
        cout << convertToString(nextAirport -> airportCode, 3) << "-";
        nextAirport = nextAirport -> nextInCloud;
    }
    Vertex *finalAirport = getVertex(end);
    cout << finalAirport -> tvalue << "\n";


}



int main(int argc, char *argv[]){

    //the user will enter the airport starting and ending points as strings in the command line; get them
    string startingPoint = argv[1];
    string endingPoint = argv[2];

    // BUILDING THE GRAPH FROM DATA
    buildHashArray();
    buildAdjacencyLists();

    //the source vertex must be the starting point
    Vertex *v = getVertex(startingPoint);

    // FINDING THE SHORTEST TIME TREE; finds quickest paths to all airports from the source
    Dijkstra(v);

    // FINDING QUICKEST ROUTE
    findQuickestPath(startingPoint, endingPoint);


    return 0;
}