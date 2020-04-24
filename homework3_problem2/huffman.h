//
// Created by Blue Sky on 3/26/20.
//

#ifndef HUFFMAN_COMPRESS_HUFFMAN_H
#define HUFFMAN_COMPRESS_HUFFMAN_H


#include <iostream>
#include <fstream>
#include <limits.h>
#include <bitset>
#include <stack>
#include <queue>
#include "Heap.h"
using namespace std;

typedef struct huffcode{
    int ch;
    char code[1000];
    int length;
}huffCode;

class treeNode{
public:
    double times;
    int ch;
    treeNode *ltree;
    treeNode *rtree;
    bool operator<(const treeNode &t){
        return this->times < t.times;
    }
    bool operator>(const treeNode &t){
        return this->times > t.times;
    }
};

class Huffman{
public:
    Huffman(void);
    void generateCode(treeNode *root,char *code,int length);
    void huffCode_gene();
    void print();
private:
    treeNode *root;
    huffCode *arra;
    int size;
    double counts[128];
    queue<bool> huffcode[128];
    treeNode *data;
};
#endif //HUFFMAN_COMPRESS_HUFFMAN_H
