import java.io.*;
import java.util.*;


class MinHeap{
	
    //private members
    private int arraySize;
    private int array[];
    private int heapSize;

    //constructor
    public MinHeap(int n){
        arraySize = n;
        array = new int[arraySize];
        heapSize = 0;
    }


    
    //bubbles down an element to correct position in heap
    private void heapify(int root){
        int left = 3*root + 1;
        int middle = 3*root + 2;
        int right = 3*root + 3;

        int min = root;

        if(left < heapSize && array[left] < array[min]){
                min = left;
        }	
        if(middle < heapSize && array[middle] < array[min]){
                min = middle;
        }
        if(right < heapSize && array[right] < array[min]){
                min = right;
        }

        if(min != root){
                swap(min, root);
                heapify(root);
        }
    }
    
   
    //floats element up to correct place in heap
    private void floatUp(int child){
        int parent = (child - 1)/3;

        if(parent >= 0 && array[child] < array[parent]){
                swap(child, parent);
                floatUp(parent);
        }
    }

    
    
    //inserts element
    public void insert(int value){
        heapSize++;
        array[heapSize-1] = value;
        floatUp(heapSize-1);
    }
    
    
    
    //extracts the minimum and fixes the heap
    public int extractMin(){
        swap(0, heapSize - 1);
        heapSize --; 
        heapify(0);
        return array[heapSize];
    }
    
    
    //decreases the value in a certain position to a lower value and fixes heap
    public void DecreaseKey(int pos, int value){
        array[pos] = value; 
        floatUp(pos);
    }
    


//swaps two elements in an array
    private void swap(int i, int j){
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
		
}

public class Heap {

    public static void main(String[] args) {
        
        int lastMinimum = 0;
        
        try{
            
            File fileObj = new File("inputFile.txt");
            Scanner in = new Scanner(fileObj);
            int instructionTotal = in.nextInt();
            MinHeap heap = new MinHeap(instructionTotal);
            
            //for each instruction
            for(int i = 1; i <= instructionTotal; i ++){
                
                //get the insturction name and execute the appropriate code
                String instruction = in.next();
                if(instruction.equals("IN")){ 
                        int key = in.nextInt();
                        heap.insert(key); //works in correct time?
                }else if(instruction.equals("DK")){
                        int pos = in.nextInt();
                        int value = in.nextInt();
                        heap.DecreaseKey(pos, value);
                }else{
                        lastMinimum = heap.extractMin();
                     
                } 
                
            }
            System.out.println(lastMinimum);
            in.close();
        }catch(FileNotFoundException e){
            System.out.println("file was not found");
        }
        
    }
}