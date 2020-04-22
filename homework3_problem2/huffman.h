//
// Created by Blue Sky on 3/26/20.
//

#ifndef HUFFMAN_COMPRESS_HUFFMAN_H
#define HUFFMAN_COMPRESS_HUFFMAN_H

#include "sort.h"
#include "myVector.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <math.h>
#include <bitset>
#include <stack>
#include <queue>
using namespace std;

typedef struct huffcode{
    int ch;
    char code[1000];
    int length;
}huffCode;

class Huffman{
public:
    Huffman(void);
    Huffman(string str);
    void saveTree();
    void preTravel(treeNode *root,ofstream *outFile);
    void midTravel(treeNode *root,ofstream *outFile);
    void generateCode(treenode *root,char *code,int length);
    void decompress(string inPath,string outPath);
    void huffCode_gene();
    void save_code();
    void print();
    void compress(string str,string str1);
private:
    treeNode *root;
    huffCode *arra;
    string filePath;
    string outPath;
    myVector array;
    int tree_length;
    int size;
    double counts[128];
    queue<bool> huffcode[128];
    void resetTree();
    void replaceNode(treeNode *root);
    void compressCode(ofstream *outFile,int index);
    void decode(unsigned char code,int times);
    unsigned char exchangeCode();
    void build_tree(treeNode *root,int *pre_s,int *mid_s,int start,int root_p,int end);
    void find_root(int *root_p,int *pre_s,int *mid_s,int start,int end);
    char huffSearch();
};
#endif //HUFFMAN_COMPRESS_HUFFMAN_H
