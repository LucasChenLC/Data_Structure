//
// Created by Blue Sky on 3/26/20.
//
#include "huffman.h"
Huffman::Huffman(void) {
    char str[100];
    cin.getline(str,100);
    memset(counts,0,128*sizeof(double));
    for(int i=0;i<strlen(str);i++){
        counts[str[i]]++;
    }
    int num=0;
    for(double & count : counts)
        if(count!=0)
            num++;
    data = (treeNode *)malloc(num*sizeof(treeNode));
    this->size  = num;
    num=0;
    for(int i=0;i<128;i++)
        if(counts[i]!=0) {
            data[num].times = counts[i];
            data[num].ch = i;
            data[num].ltree = NULL;
            data[num].rtree = NULL;
            num++;
        }
    miniHeap<treeNode> heap(data,size);
        treeNode mini_1,mini_2,*min1,*min2;
    for(int a=0;a<size-1;a++){
        mini_2 = heap.removeMini();
        mini_1 = heap.removeMini();
        min1 = (treeNode *)malloc(sizeof(treeNode));
        *min1=mini_1;
        min2 = (treeNode *)malloc(sizeof(treeNode));
        *min2=mini_2;
        mini_2.ltree = min1;
        mini_2.rtree = min2;
        mini_2.times = mini_2.rtree->times + mini_2.ltree->times;
        heap.insert(mini_2);
    }
        root = (treeNode *)malloc(sizeof(treeNode));
        *root = heap.removeMini();
        for(double & count : counts)
            count/=strlen(str);
    return;
}

void Huffman::huffCode_gene() {
    char code[128];
    arra = (huffCode *)malloc(128*sizeof(huffCode));
    generateCode(root,code,0);
    return;
}

void Huffman::generateCode(treeNode *root,char *code,int length){
    if(root->ltree==NULL && root->rtree==NULL){
        int num = root->ch;
        for(int a=0;a<length;a++) {
            huffcode[num].push((bool)code[a]);
        }
        arra[num].length = length;
        arra[num].ch = root->ch;
        return;
    }
    else{
        code[length]=1;
        generateCode(root->ltree,code,length+1);
        code[length]=0;
        generateCode(root->rtree,code,length+1);
    }
}

void Huffman::print() {
    bool find;
    while(true) {
        int p=0;
        find = false;
        for(int i=0;i<128;i++)
        {
            if(counts[i]>counts[p] && counts[i]>0) {
                p = i;
                find = true;
            }
        }
        if (!huffcode[p].empty()) {
                cout << (char) p << ":";
            cout<<fixed<<setprecision(2) <<counts[p]<<":";
                while (!huffcode[p].empty()) {
                    cout << huffcode[p].front();
                    huffcode[p].pop();
                }
                cout << endl;
        }
        counts[p]=0;
        if(!find)
            break;
    }
}


