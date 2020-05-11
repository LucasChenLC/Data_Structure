//
// Created by Blue Sky on 4/22/20.
//

#include <iostream>
#include "Heap.h"
using namespace std;

class Sort {
public:
    int *array;
    int num;
    Sort();
    void print();
};

int main(void){
    Sort s;

}

Sort::Sort() {
    cin>>num;
    array = (int *)malloc(num*sizeof(int));
    for(int i=0;i<num;i++)
        cin>>array[i];
    Heap h(array,num);
    h.print();
    while(!h.empty()){
        cout<<h.removeMax()<<" ";
    }
    cout<<endl;
}

void Sort::print() {
    for(int i=0;i<num;i++)
        cout<<array[i]<<" ";
    cout<<endl;
}
