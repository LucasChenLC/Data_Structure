#include <iostream>

#include <iostream>
using namespace std;
void josephusArray(int n,int s,int m);

int main() {
    int n,s,m;
    cin>>n>>s>>m;
    josephusArray(n,s,m);
    return 0;
}

void josephusArray(int n,int s,int m){
    int *array = (int *)malloc(n*sizeof(int)),index=s-1;
    for(int i=0;i<n;i++)
        array[i] = i+1;
    while(true){
        for(int i=1;i<m;i++)
        {
            index = (index+1)%n;
            if(array[index]<0)
                i--;
        }
        cout<<array[index]<<" ";
        array[index] = -1;


        bool flag = true;
        for(int i=0;i<n;i++){
            if(array[i]>0)
                flag = false;
        }
        if(flag)
            break;
        for(int i=(index+1)%n;;i=(i+1)%n)
        {
            if(array[i]>0) {
                index = i;
                break;
            }
        }
    }
}
