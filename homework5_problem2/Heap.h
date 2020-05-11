//
// Created by Blue Sky on 4/22/20.
//

#ifndef HEAP_SORT_HEAP_H
#define HEAP_SORT_HEAP_H
#include <iostream>
class Heap{
public:
    Heap(int *array,int num);
    int removeMax();
    bool empty();
    void print();
private:
    int *array;
    int num;
    void shiftDown(int start);
};

Heap::Heap(int *array, int num) {
    this->array = (int *)malloc(num*sizeof(int));
    for(int i=0;i<num;i++)
        this->array[i] = array[i];
    this->num = num;
    for(int i=(num-1)/2;i>=0;i--)
    {
        shiftDown(i);
    }
    return;
}

int Heap::removeMax() {
    int ans = array[0];
    num--;
    array[0] = array[num];

    shiftDown(0);
    return ans;
}

bool Heap::empty() {
    return !num;
}

void Heap::print(){
    for(int i=0;i<num;i++)
        std::cout<<array[i]<<" ";
    std::cout<<std::endl;
}
void Heap::shiftDown(int start){
    int max,temp;
    while(start*2+1<num){
        max=start*2+1;
        if(start*2+2<num && array[start*2+2]>array[start*2+1])
            max++;
        if(array[start]<array[max])
        {
            temp = array[start];
            array[start] = array[max];
            array[max] = temp;
            start = max;
        }
        else
            break;
    }
}


#endif //HEAP_SORT_HEAP_H
