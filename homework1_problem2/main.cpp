#include <iostream>
using namespace std;
typedef struct node{
    int data;
    struct node *next;
}Node;
void josephusLinkList(int n,int s,int m);

int main() {
    int n,s,m;
    cin>>n>>s>>m;
    josephusLinkList(n,s,m);
    return 0;
}

void josephusLinkList(int n,int s,int m){
    //构造单循环链表
    Node *head,*x,*t;
    head=(Node *)malloc(sizeof(Node));
    t=head;
    for(int a=0;a<n;a++){
        x=(Node *)malloc(sizeof(Node));
        x->data=a+1;
        t->next=x;
        t=t->next;
    }
    head=head->next;
    t->next=head;
    t=head;

    for(;t->next->data!=(s+m-1)%n;t = t->next){}

    //开始解题
    while(t->next!=t) {
        cout<<t->next->data<<" ";
        t->next=t->next->next;
        for(int i=0;i<m-1;i++)
            t=t->next;
    }
    cout<<t->data;
}