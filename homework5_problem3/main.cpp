//
// Created by Blue Sky on 4/22/20.
//
#include <iostream>
using namespace std;

class Sort {
public:
    int *array;
    int num;
    Sort();
    void mergeSort();
    void print();
private:
    void modMergeSort(int start,int end);
    void merge(int start,int mid,int end);
};

int main(void){
    Sort s;
    s.mergeSort();
    s.print();
}

Sort::Sort() {
    cin>>num;
    array = (int *)malloc(num*sizeof(int));
    for(int i=0;i<num;i++)
        cin>>array[i];
}

void Sort::mergeSort() {
    modMergeSort(0,num-1);
}

void Sort::modMergeSort(int start, int end) {
    if(start>=end)
        return;
    else{
        modMergeSort(start,start+(end-start)/2);
        modMergeSort(start+(end-start)/2+1,end);
        merge(start,start+(end-start)/2+1,end);
    }
}

void Sort::merge(int start, int mid, int end) {
    int num = end-start+1;
    int count=0,l=start,h=mid;
    int *temp_array = (int *)malloc(num*sizeof(int));
    while(count<num)
    {
        if(l<mid && h<=end){
            if(array[l]<array[h]){
                temp_array[count] = array[l];
                l++;
            }
            else{
                temp_array[count] = array[h];
                h++;
            }
        }
        else if(l<mid){
            temp_array[count] = array[l];
            l++;
        }
        else if(h<=end){
            temp_array[count] = array[h];
            h++;
        }
        count++;
    }
    for(int i=0;i<num;i++)
        array[start+i] = temp_array[i];
}

void Sort::print() {
    for(int i=0;i<num;i++)
        cout<<array[i]<<" ";
    cout<<endl;
}