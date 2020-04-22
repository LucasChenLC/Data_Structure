//
// Created by Blue Sky on 3/29/20.
//
#include "myVector.h"

myVector::myVector(){
    length = 0;
    head = NULL;
};

void myVector::insert_back(int data) {
    if(head==NULL){
        head = (Node *)malloc(sizeof(Node));
        head->data = data;
        head->next = NULL;
        length++;
    }
    else{
        Node *n = (Node *)malloc(sizeof(Node)),*temp=head;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next = n;
        n->data = data;
        n->next = NULL;
        length++;
    }
}

void myVector::insert_front(int data) {
    if(head==NULL){
        head = (Node *)malloc(sizeof(Node));
        head->data = data;
        head->next = NULL;
        length++;
    }
    else{
        Node *n = (Node *)malloc(sizeof(Node));
        n->data = data;
        n->next = head;
        head = n;
        length++;
    }
}

void myVector::clear(){
    head = NULL;
    length=0;
}
int myVector::pop(){
    int ans = head->data;
    length--;
    head = head->next;
    return ans;
}

int myVector::size(){
    return length;
}

bool myVector::empty(){
    if(length)
        return false;
    return true;
}
