/*

gatorTaxi Application (Terminal Application) based on modified Heap and Red Black tree 
Submitted by Raj Shukla (UFID: 86317877)


*/

/*
****************************
*                          *
*         GatorTaxi        *         BY RAJ SHUKLA
*                          *
****************************
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


// This is a Single Min Heap Node
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

// This is the node structure for our Red Black Tree
struct Node{
  int data_r_num; // holds the ride number
  int data_r_cost; // holds ride cost
  int data_r_duration;
  Node *parent; // pointer to the parent
  Node *left; // pointer to left child
  Node *right; // pointer to right child
  int color; // 1 -> Red, 0 -> Black
};
typedef Node* NodePtr;


// class RBTree implements the operations in Red Black Tree
class RBTree {
private:
  NodePtr root;
  NodePtr tempPtr;   //Leaf / NULL black nodes

  // initializes the nodes with appropirate values
  // all the pointers are set to point to the null pointer
  void initializeNULLNode(NodePtr node, NodePtr parent) {
    node->data_r_num = 0;
    node->data_r_cost = 0;
    node->data_r_duration = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
  }

  
  //Single search Utility
  NodePtr searchTreeHelper(NodePtr root, int search_key) {
    if(root == tempPtr){
      return nullptr;
    }
    if (search_key == root->data_r_num) {
      return root;
    }

    if (search_key < root->data_r_num) {
      return searchTreeHelper(root->left, search_key);
    } 
    return searchTreeHelper(root->right, search_key);
  }

  //Range Search Utility
  void searchRangeInTreeHelper(NodePtr root, int a, int b, vector<NodePtr>& result){
    if (root==tempPtr)
        return; 
    //recursively call the left subtree
    searchRangeInTreeHelper(root->left, a, b, result);
    //if root's data lies in range,then prints root's data
    if (a <= root->data_r_num && b >= root->data_r_num)result.push_back(root);
    //recursively call the right subtree
    searchRangeInTreeHelper(root->right, a, b, result);
  }



  // fix the rb tree modified by the delete operation
  //  NOTE: All the cases can be referred in the report.

  void fixDelete(NodePtr x) {
    NodePtr s;
    while (x != root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          // case 3.1
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0) {
          // case 3.2
          s->color = 1;
          x = x->parent;
        } 
        else{
          if (s->right->color == 0) {
            // case 3.3
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
          } 

          // case 3.4
          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotate(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          // case 3.1
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->right->color == 0) {
          // case 3.2
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            // case 3.3
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
          } 

          // case 3.4
          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotate(x->parent);
          x = root;
        }
      } 
    }
    x->color = 0;
  }

  // Red Black transplant Utility function. Refer to the report
  void rbTransplant(NodePtr u, NodePtr v){
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left){
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }


  // Sub Utility to delete node and check for grand parent and parent discrepencies
  void deleteNodeHelper(NodePtr node, int search_key) {
    // find the node containing search_key
    NodePtr z = tempPtr;
    NodePtr x, y;
    while (node != tempPtr){
      if (node->data_r_num == search_key) {
        z = node;
      }

      if (node->data_r_num <= search_key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == tempPtr) {
      //Absent
      return;
    } 

    y = z;
    int y_original_color = y->color;
    if (z->left == tempPtr) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == tempPtr) {
      x = z->left;
      rbTransplant(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == 0){
      // Fix upper level discripencies with one more sub utility.
      fixDelete(x);
    }
  }
  
  // fix the red-black tree post insertion to avoid r-r conflict
  void fixInsert(NodePtr k){
    NodePtr u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left; // uncle
        if (u->color == 1) {
          // case 3.1
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            // case 3.2.2
            k = k->parent;
            rightRotate(k);
          }
          // case 3.2.1
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right; // uncle

        if (u->color == 1) {
          // mirror case 3.1
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;  
        } else {
          if (k == k->parent->right) {
            // mirror case 3.2.2
            k = k->parent;
            leftRotate(k);
          }
          // mirror case 3.2.1
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0;
  }

public:
  //Initailize RBT root as Leaf NULL.
  RBTree() {
    tempPtr = new Node;
    tempPtr->color = 0;
    tempPtr->left = nullptr;
    tempPtr->right = nullptr;
    root = tempPtr;
  }

  // search the tree for the search_key k
  // and return the corresponding node. Following the interface function.
  NodePtr searchTree(int k) {
    return searchTreeHelper(this->root, k);
  }

  // range search interface function.
  vector<NodePtr> searchRangeInTree(int a, int b){
    vector<NodePtr> result;
    searchRangeInTreeHelper(this->root,a,b,result);
    return result;
  }

  // find the node with the minimum key
  NodePtr minimum(NodePtr root) {
    while (root->left != tempPtr) {
      root = root->left;
    }
    return root;
  }

  // find the node with the maximum key
  NodePtr maximum(NodePtr root) {
    while (root->right != tempPtr) {
      root = root->right;
    }
    return root;
  }
  // find the successor of a given node with the following utility
  NodePtr successor(NodePtr x) {
    if (x->right != tempPtr) {
      return minimum(x->right);
    }
    // else it is the lowest ancestor of x whose
    // left child is also an ancestor of x.
    NodePtr y = x->parent;
    while (y != tempPtr && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }
  // find the predecessor of a given node with the following utility
  NodePtr predecessor(NodePtr x) {
    // if the left subtree is not null,the predecessor is the rightmost node in the leftsubtree
    if (x->left != tempPtr) {
      return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != tempPtr && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  // Left rotate utility on given node
  void leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != tempPtr) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  // Right rotate utility on the given node
  void rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != tempPtr) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // insert the key to the tree in its appropriate position
  // and fix the tree with fix insert sub utility
  void insert(int r_num, int r_cost, int r_duration) {
    // Ordinary Binary Search Insertion
    NodePtr node = new Node;
    node->parent = nullptr;
    node->data_r_num = r_num;
    node->data_r_cost = r_cost;
    node->data_r_duration = r_duration;
    node->left = tempPtr;
    node->right = tempPtr;
    node->color = 1; // new node must be red

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != tempPtr) {
      y = x;
      if (node->data_r_num < x->data_r_num) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    // y is parent of x
    node->parent = y;
    if (y == nullptr) {
      root = node;
    } else if (node->data_r_num < y->data_r_num) {
      y->left = node;
    } else {
      y->right = node;
    }

    // if new node is a root node, simply return
    if (node->parent == nullptr){
      node->color = 0;
      return;
    }

    // if the grandparent is null, simply return
    if (node->parent->parent == nullptr) {
      return;
    }
    // Check the tree and fix if needed
    fixInsert(node);
  }

  // NodePtr getRoot(){
  //   return this->root;
  // }

  // delete the node from the tree
  void deleteNode(int data) {
    deleteNodeHelper(this->root, data);
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
    //check if the left child index is in range
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
        
      }

      return;
    }


public:
    MinHeap() {}

    //Interface method for min heap insertion. Utilizes Bubble up.
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

    // returns min Element top of min Heap and deletes it. This is an interface fuction which internally uses removeMin utility and Bubbledown fuctions.
    HeapNode minElement(){
        if (heap.empty()) {
            HeapNode x(-1,-1,-1);
            return x;
        }
        HeapNode response = heap[0];
        removeMin();
        return response;
    }

    //RemoveMin utility . Involves Bubble down step.
    void removeMin() {
        if (heap.empty()) {
            return;
        }
        int last_index=heap.size()-1;
        //update top element with last element in the heap and then bubble down
        heap[0].r_cost = heap[last_index].r_cost;
        heap[0].r_num = heap[last_index].r_num;
        heap[0].r_duration = heap[last_index].r_duration;
        heap.pop_back();
        bubbleDown(0);
        return;
    }

    //Arnitrary remove and heapify. WC = O(nlog(n)). Avg Case = log(n)
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


// Input file parser utility function.
// checks input function given and returns arguments in integer vector.
vector<int> parseArg(string s){
    int i=0;
    while(s[i]!='(')i++;
    int j=s.size()-1;
    i++;
    vector<int> v;
    string ss;
    while(i!=j){
        if(s[i]!=','){
            ss+=s[i];
        }else{
            int x=stoi(ss);
            ss="";
            v.push_back(x);
        }i++;
    }
    v.push_back(stoi(ss));
    return v;
}


int main(int argc, char* argv[]) {
    // Check that an input file name and an output file name were provided as command-line arguments
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    // Open the input file for reading
    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cout << "Error: could not open input file: " << argv[1] << endl;
        return 1;
    }

    // Open the output file for writing
    ofstream output_file("output_file.txt");
    if (!output_file.is_open()) {
        cout << "Error: could not open output file: output.txt" << endl;
        return 1;
    }
    MinHeap heap;
    RBTree bst;

    // Read input from the input file and process it
    string line;
    while (getline(input_file, line)) {
        //INSERT function
        if(line[0]=='I'){
            vector<int> v=parseArg(line);
            if(bst.searchTree(v[0]) != nullptr){
                output_file<<"Duplicate RideNumber"<<endl;
                continue;
            }
            heap.insert(v[0],v[1],v[2]);
            bst.insert(v[0],v[1],v[2]);
        }//GetNextRide function
        else if(line[0]=='G'){
            if(heap.len()==0){
                output_file<<"No active ride requests"<<endl;
            }else{
                HeapNode ret = heap.minElement();
                int search_key = ret.r_num;
                bst.deleteNode(search_key);
                output_file<<"("<<search_key<<","<<ret.r_cost<<","<<ret.r_duration<<")"<<endl;
            }
        } //Cancel Ride Function
        else if(line[0]=='C'){
            vector<int> v=parseArg(line);
            if(bst.searchTree(v[0])!=nullptr){
                heap.cancle(v[0]);
                bst.deleteNode(v[0]);
            }
        } //Update Ride Function
        else if(line[0]=='U'){
            vector<int> v=parseArg(line);
            int new_Trip_duration = v[1];
            NodePtr targetNode = bst.searchTree(v[0]);
            int existing_Trip_duration = targetNode->data_r_duration;
            int existing_Trip_cost = targetNode->data_r_cost;
            // Following are the updateion rules in the if else block as per the requirement.
            if(existing_Trip_duration >= new_Trip_duration){
                heap.cancle(v[0]);
                targetNode->data_r_duration = new_Trip_duration;
                heap.insert(v[0],existing_Trip_cost,new_Trip_duration);
            }else if(new_Trip_duration > existing_Trip_duration && new_Trip_duration <= 2*existing_Trip_duration){
                heap.cancle(v[0]);
                targetNode->data_r_duration = new_Trip_duration;
                targetNode->data_r_cost = existing_Trip_cost+10;
                heap.insert(v[0],existing_Trip_cost+10,new_Trip_duration);
            }else{
                heap.cancle(v[0]);
                bst.deleteNode(v[0]);
            }
        } 
        else if(line[0]=='P'){
            vector<int> v=parseArg(line);
            //Single Print and Range Print Functionalities via following if-else block.
            if(v.size()==1){
                NodePtr x = bst.searchTree(v[0]);
                if(x!=nullptr){
                    output_file<<"("<<x->data_r_num<<","<<x->data_r_cost<<","<<x->data_r_duration<<")"<<endl;
                }else{
                    output_file<<"(0,0,0)"<<endl;
                }
            }else{
                vector<NodePtr> res = bst.searchRangeInTree(v[0],v[1]);
                if(res.size()>0){
                    for(int i=0;i<res.size();i++){
                        output_file<<"("<<res[i]->data_r_num<<","<<res[i]->data_r_cost<<","<<res[i]->data_r_duration<<")";
                        if(i!=res.size()-1){
                            output_file<<",";
                        }
                    }output_file<<endl;
                }else{
                    output_file<<"(0,0,0)"<<endl;
                }
            }
        }
        else{
            continue;
        }
    }

    // Close the input and output files
    input_file.close();
    output_file.close();

    return 0;
}
