/*Segment tree trivia: number of leaf nodes = number of elements in the given array = n;
                       number of internal nodes in segment tree = number of internal nodes in a tree = n-1;
                       total number of nodes in a segment tree = n + n-1 = 2*n-1; */
//Hence total size of segment tree array = 2*n;

#include <iostream>

using namespace std;
void buildtree(int * arr,int * tree, int start, int end, int treeNodeIndex){
    if(start==end){
        tree[treeNodeIndex]=arr[start];
        return;
    }
    int mid=start+(end-start)/2;
    buildtree(arr,tree,start,mid,2*treeNodeIndex);
    buildtree(arr,tree,mid+1,end,2*treeNodeIndex+1);
    tree[treeNodeIndex]=tree[2*treeNodeIndex]+tree[2*treeNodeIndex+1];  //sum
    return;
}
void updateTree(int * arr,int * tree, int start, int end, int treeNodeIndex, int idx, int val){
    if(start==end){
        tree[treeNodeIndex]=val;
        arr[idx]=val;
        return;
    }
    int mid=start+(end-start)/2;
    if(mid>idx){
        updateTree(arr,tree,start,mid,2*treeNodeIndex,idx,val);
    }else{
        updateTree(arr,tree,mid+1,end,2*treeNodeIndex+1,idx,val);
    }
    tree[treeNodeIndex]=tree[2*treeNodeIndex+1]+tree[2*treeNodeIndex];  //sum
    return;
}
int queryTree(int *  tree, int start, int end, int left, int right, int treeNodeIndex){
    //completely outside
    if(start>right||end<left){
        return 0;
    }
    //completely inside
    if(right>=end&&left<=start){
        return tree[treeNodeIndex];
    }
    //partial
    int mid=start+(end-start)/2;
    int ans1=queryTree(tree,start,mid,left,right,2*treeNodeIndex);
    int ans2=queryTree(tree,mid+1,end,left,right,2*treeNodeIndex+1);
    return ans1+ans2; //Important.
}
int main()
{
    //Given Array;
    int arr[]={1,2,3,4,5,7,9};
    int *tree=new int[14];
    buildtree(arr,tree,0,6,1);
    //Print built tree;
    for(int i=1;i<14;i++){
        cout<<tree[i]<<" ";
    }cout<<endl;
    updateTree(arr,tree,0,6,1,3,13);
    //Print after update
    for(int i=1;i<14;i++){
        cout<<tree[i]<<" ";
    }cout<<endl;
    
    
    
    return 0;
}