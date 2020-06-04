    //
// Created by Blue Sky on 4/24/20.
//

#ifndef HUFFMAN_HEAP_H
#define HUFFMAN_HEAP_H
#include <iostream>
#include "huffman.h"

template <class T>
class miniHeap{
public:
    miniHeap(T *array,int num);
    T removeMini();
    bool empty();
    int size();
    void insert(T n);
    void print();
private:
    T *array;
    T *temp;
    int num;
    void shiftDown(int start);
    void shiftUp(int start);
};

template <class T>
miniHeap<T>::miniHeap(T *array, int num) {
   this->array = (T *)malloc(num*sizeof(T));
    for(int i=0;i<num;i++)
        this->array[i] = array[i];
    this->num = num;
    for(int i=(num-1)/2;i>=0;i--)
        shiftDown(i);

}

template <class T>
T miniHeap<T>::removeMini() {
    temp = (T *)malloc(sizeof(T));
    *temp = array[0];
    num--;
    array[0] = array[num];
    shiftDown(0);
    return *temp;
}

template <class T>
bool miniHeap<T>::empty() {
    return !num;
}

template <class T>
int miniHeap<T>::size() {
    return num;
}

template <class T>
void miniHeap<T>::shiftDown(int start) {
    int mini;
    T temp;
    while(start*2+1<num){
        mini=start*2+1;
        if(start*2+2<num && array[start*2+2]<array[start*2+1])
            mini++;
        if(array[start]>array[mini])
        {
            temp = array[start];
            array[start] = array[mini];
            array[mini] = temp;
            start = mini;
        }
        else
            break;
    }
}

template <class T>
void miniHeap<T>::insert(T n){
    array[num] = n;
    shiftUp(num);
    this->num++;
}

template <class T>
void miniHeap<T>::shiftUp(int start) {
    T temp;
    while((start-1)/2>=0&&array[start]<array[(start-1)/2]){
        temp = array[start];
        array[start] = array[(start-1)/2];
        array[(start-1)/2] = temp;
        start = start/2-1;
    }
}

template <class T>
void miniHeap<T>::print() {
    for(int i=0;i<num;i++)
        std::cout<<array[i].times<<" ";
    std::cout<<std::endl;
}

#endif //HUFFMAN_HEAP_H
