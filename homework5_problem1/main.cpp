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
    void quickSort();
    void print();
private:
    void modQuickSort(int start,int end);
};

int main(void){
    Sort s;
    s.quickSort();
    s.print();
}

Sort::Sort() {
    cin>>num;
    array = (int *)malloc(num*sizeof(int));
    for(int i=0;i<num;i++)
        cin>>array[i];
}

void Sort::print() {
    for(int i=0;i<num;i++)
        cout<<array[i]<<" ";
    cout<<endl;
}

void Sort::quickSort(){
    modQuickSort(0,num-1);
}

void Sort::modQuickSort(int start,int end){
    if(start>=end)
        return;
    else{
        int l = start,h=end,pivot = array[start];
        while(true){
            while(array[h]>pivot && h!=l)
            {
                h--;
            }
            if(h==l)
                break;
            array[l] = array[h];
            while(array[l]<=pivot && h!=l)
            {
                l++;
            }
            if(h==l)
                break;
            array[h] = array[l];
        }
        array[h] = pivot;
        modQuickSort(start,h-1);
        modQuickSort(h+1,end);
    }
}
