#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
struct HeapNode{
    int r_num;
    int r_cost;
    int r_duration;
    HeapNode(int number,int cost,int duration){
        r_num=number;
        r_cost=cost;
        r_duration=duration;
    }
};
class MinHeap {

private:
    vector<HeapNode> heap;
    //index of parent
    int parent(int i) const {
        return (i - 1) / 2;
    }
    //index of left child
    int leftChild(int i) const {
        return 2 * i + 1;
    }
    //index of right child
    int rightChild(int i) const {
        return 2 * i + 2;
    }
    bool hasLeftChild(int i) {
      return leftChild(i) < heap.size();
    }   
    // Helper function to check if a node has a right child
    bool hasRightChild(int i) {
      return rightChild(i) < heap.size();
    }
    // Helper function to check if a node is a leaf node
    bool isLeafNode(int i) {
      return !hasLeftChild(i) && !hasRightChild(i);
    }
    //Helper for swapping
    void swapNodes(int i, int j) {
      HeapNode temp = heap[i];
      heap[i] = heap[j];
      heap[j] = temp;
    }
    //move node up the Heap as per criterea
    void bubbleUp(int i) {
      while (i > 0 && heap[i].r_cost < heap[parent(i)].r_cost) {
        swapNodes(i, parent(i));
        i = parent(i);
      }
      // If key1 values are equal
      if (i > 0 && heap[i].r_cost == heap[parent(i)].r_cost && heap[i].r_duration < heap[parent(i)].r_duration) {
        swapNodes(i, parent(i));
        bubbleUp(parent(i));
      }
    }
        
    // Helper function to move a node down the heap
    void bubbleDown(int i) {
      while (!isLeafNode(i)) {
        int smallestChildIndex = leftChild(i);
        if (hasRightChild(i) && heap[rightChild(i)].r_cost < heap[smallestChildIndex].r_cost) {
          smallestChildIndex = rightChild(i);
        }
        // If cost values are equal, then compare duration values to maintain minheap property
        if (hasRightChild(i) && heap[rightChild(i)].r_cost == heap[smallestChildIndex].r_cost && heap[rightChild(i)].r_duration < heap[smallestChildIndex].r_duration) {
          smallestChildIndex = rightChild(i);
        }
        if (heap[i].r_cost < heap[smallestChildIndex].r_cost) {
          break;
        }
        if (heap[i].r_cost > heap[smallestChildIndex].r_cost) {
          swapNodes(i, smallestChildIndex);
          i = smallestChildIndex;
          continue;
        }
        if(heap[i].r_cost == heap[smallestChildIndex].r_cost){
          if(heap[i].r_duration < heap[smallestChildIndex].r_duration){
            swapNodes(i, smallestChildIndex);
            i = smallestChildIndex;
          }else{
            break;
          }
        }
        
      }return;
    }
    
public:
    MinHeap() {}

    void insert(int number, int cost, int duration) {
        HeapNode value(number,cost,duration);
        heap.push_back(value);
        int i = heap.size() - 1;
        bubbleUp(i);
        return;
    }
    //heap size utility public function
    int len(){
        return heap.size();
    }
    HeapNode minElement(){
        if (heap.empty()) {
            HeapNode x(-1,-1,-1);
            return x;
        }
        HeapNode response = heap[0];
        removeMin();
        return response;
    }

    void removeMin() {
        if (heap.empty()) {
            return;
        }
        cout<<heap[0].r_num<<"---"<<heap[0].r_cost<<"---"<<heap[0].r_duration<<endl;
        int last_index=heap.size()-1;
        //update top element with last element in the heap and then bubble down
        heap[0].r_cost = heap[last_index].r_cost;
        heap[0].r_num = heap[last_index].r_num;
        heap[0].r_duration = heap[last_index].r_duration;
        //cout<<heap[0].r_num<<"---"<<heap[0].r_cost<<"---"<<heap[0].r_duration<<endl;
        heap.pop_back();
        bubbleDown(0);
        return;
    }


    void cancle(int rnum){
        vector<HeapNode> temp;
        for(int i=0;i<heap.size();i++){
            if(heap[i].r_num!=rnum){
                temp.push_back(heap[i]);
            }
        }
        heap.clear();
        for(int i=0;i<temp.size();i++){
            insert(temp[i].r_num,temp[i].r_cost,temp[i].r_duration);
        }
        return;
    }
        
};
int main(){
  MinHeap heapp;
  heapp.insert(1,12,30);
  heapp.insert(2,12,12);
  heapp.insert(3,12,19);
  heapp.insert(4,12,14);
  
  heapp.removeMin();
  heapp.removeMin();
  heapp.removeMin();
  heapp.removeMin();
  heapp.removeMin();
  heapp.removeMin();
  
}