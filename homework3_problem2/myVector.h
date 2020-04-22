//
// Created by Blue Sky on 3/29/20.
//

#ifndef HUFFMAN_COMPRESS_MYVECTOR_H
#define HUFFMAN_COMPRESS_MYVECTOR_H
#include <iostream>
typedef struct node{
    int data;
    struct node *next;
}Node;

class myVector{
public:
    myVector();
    void insert_front(int data);
    void insert_back(int data);
    void clear();
    int pop();
    int size();
    bool empty();
private:
    int length;
    Node *head;
};
#endif //HUFFMAN_COMPRESS_MYVECTOR_H
