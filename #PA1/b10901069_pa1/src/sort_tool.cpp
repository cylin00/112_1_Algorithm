// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<limits>
#define ll long long 
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int i, j, key;
    for(j=1;j<data.size();j++){
        key = data[j];
        i = j-1;
        while(i>=0 && data[i]>key){
            data[i+1] = data[i];
            i = i-1;
        }
        data[i+1] = key;
    }
    //d!
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    if(flag==0){
        if(low<high){
            int q = Partition(data, low, high);
            QuickSortSubVector(data, low, q, flag);
            QuickSortSubVector(data, q+1, high, flag);
        }
    }
    // flag == 1 -> randomized QS
    if(flag==1){
        if(low<high){
            int q = RandomizedPartition(data, low, high);
            QuickSortSubVector(data, low, q, flag);
            QuickSortSubVector(data, q+1, high, flag);
        }
    }
    //d!
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    //p=low, r=high
    int range = high - low + 1;
    int i = rand() % range + low;
    int k = data[i];
    data[i] = data[low];
    data[low] = k;
    return Partition(data, low, high);
    //d!
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    //p=low, r=high
    int x = data[low];
    int i = low-1;
    int j = high+1;
    while(true){
        do{
            j = j-1;
        }while(data[j]>x);

        do{
            i = i+1;
        }while(data[i]<x);

        if(i<j){
            int k = data[i];
            data[i] = data[j];
            data[j] = k;
        }
        else return j;
    }
    //d!
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low < high){
        int q = (low+high)/2;
        MergeSortSubVector(data, low, q);
        MergeSortSubVector(data, q+1, high);
        Merge(data, low, q, q+1, high);
    }
    //d!
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    // low=p, middle1=q, middle2=q+1, high=r
    int n1 = middle1 - low + 1;
    int n2 = high - middle1;
    int L[n1+1];
    int R[n2+1];
    for(int i=0;i<n1;i++){
        L[i] = data[low+i]; 
    }
    for(int j=0;j<n2;j++){
        R[j] = data[middle1+j+1];
    }
    L[n1] = 1000001;
    R[n2] = 1000001;
    int i=0, j=0;
    for(int k=low;k<=high;k++){
        if(L[i]<=R[j]){
            data[k] = L[i];
            i = i+1;
        }
        else{
            data[k] = R[j];
            j = j+1;
        }
    }
    //d?
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = root*2+1;
    int r = root*2+2;
    int largest;
    if(l<heapSize && data[l]>data[root]) largest = l;
    else largest = root;
    if(r<heapSize && data[r]>data[largest]) largest = r;
    if(largest!=root){
        int x = data[largest];
        data[largest] = data[root];
        data[root] = x;
        MaxHeapify(data, largest);
    }
    //d!
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i=(data.size()/2)-1;i>=0;i--){
        MaxHeapify(data, i);
    }
    //d!
}
