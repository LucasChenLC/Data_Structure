//
// Created by Blue Sky on 3/25/20.
//

#include "sort.h"

treeNode *merge_sort_cp(double *counts,int *num){
    int count=0,index=0;
    for(int a=0;a<128;a++){
        if(counts[a]!=0){
            count++;
        }
    }
    treeNode *arra = (treeNode *)malloc(count*sizeof(treeNode));
    for(int a=0;a<count;a++){
        while(true) {
            if (counts[index] != 0) {
                index++;
                break;
            } else
                index++;
        }
        arra[a].ch = index-1;
        arra[a].times = counts[index-1];
        arra[a].rtree = NULL;
        arra[a].ltree = NULL;
    }
    merge_sort(arra,count);
    *num = count;
    return arra;
}

void merge_sort(treeNode *list,int length){
    if(length<2){
        return;
    }
    else{
        treeNode *right,*left;
        right=(treeNode *)malloc((length/2)*sizeof(treeNode));
        left=(treeNode *)malloc((length-length/2)*sizeof(treeNode));
        for(int a=0;a<length/2;a++)
            right[a]=list[a];
        for(int a=length/2;a<length;a++)
            left[a-length/2]=list[a];
        merge_sort(right,length/2);
        merge_sort(left,length-length/2);
        merge(list,right,left,length);
    }
}

void merge(treeNode *list,treeNode *right,treeNode *left,int length){
    int index_r=0,index_l=0,index=0;
    while(index<length){
        if(index_r==length/2){
            while(index_l<length-length/2){
                list[index]=left[index_l];
                index++;
                index_l++;
            }
            break;
        }
        if(index_l==length-length/2)
        {
            while(index_r<length/2){
                list[index]=right[index_r];
                index++;
                index_r++;
            }
            break;
        }
        if(right[index_r].times<left[index_l].times){
            list[index]=right[index_r];
            index_r++;
        }
        else{
            list[index]=left[index_l];
            index_l++;
        }
        index++;
    }
}
