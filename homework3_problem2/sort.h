//
// Created by Blue Sky on 3/25/20.
//

#ifndef HUFFMAN_COMPRESS_SORT_H
#define HUFFMAN_COMPRESS_SORT_H
#include <iostream>
#include <stdlib.h>

typedef struct treenode{
    long times;
    int ch;
    struct treenode *ltree;
    struct treenode *rtree;
}treeNode;


treeNode *merge_sort_cp(double *counts,int *num);
void merge_sort(treeNode *list,int length);
void merge(treeNode *list,treeNode *right,treeNode *left,int length);

#endif //HUFFMAN_COMPRESS_SORT_H
