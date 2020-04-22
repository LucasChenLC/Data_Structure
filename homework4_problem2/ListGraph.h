//
// Created by Blue Sky on 4/15/20.
//

#ifndef GRAPH_LISTGRAPH_H
#define GRAPH_LISTGRAPH_H

#include "Graph.h"
#include <iostream>
#include "Edge.h"
using namespace std;
template <class T1,class T2>
class ListGraph: public Graph<T1,T2>{
private:
    Vertex<T1,T2> *vertexList;

public:
    explicit ListGraph(int vertexNum,int arcNum,Edge<T1,T2> *arcs);
    void addArc(T1 fromVertexID,T1 toVerTexID,T2 weight);
    bool getArc(T1 fromVertexID,T1 &toVertexID,T2 &weight);
    void clearFlag();
    void clearFlag(T1 index);
    void print();
    T1 getID(T1 index);
};

template <class T1,class T2>
ListGraph<T1,T2>::ListGraph(int vertexNum,int arcNum,Edge<T1,T2> *arcs):Graph<T1,T2>(vertexNum,arcNum) {
    this->vertexNum = vertexNum;
    this->vertexList = new Vertex<T1,T2>[vertexNum];
    for(int i=0;i<vertexNum;i++) {
        vertexList[i].vertexID = -1;
        vertexList[i].next = NULL;
    }
    for(int i=0;i<arcNum;i++)
    {
        bool flag1 = true,flag2 = true;
        int e;
        for(e=0;e<vertexNum&&vertexList[e].vertexID!=-1;e++){
            if(arcs[i].fromVertex == vertexList[e].vertexID)
                flag1 = false;
            if(arcs[i].toVertex == vertexList[e].vertexID)
                flag2 = false;
        }
        if(flag1) {
            vertexList[e].vertexID = arcs[i].fromVertex;
            e++;
        }
        if(flag2)
            vertexList[e].vertexID = arcs[i].toVertex;
    }
    for(int i=0;i<vertexNum;i++)
    {
        for(int e=i;e<vertexNum;e++){
            if(vertexList[i].vertexID>vertexList[e].vertexID) {
                T1 temp = vertexList[i].vertexID;
                vertexList[i].vertexID = vertexList[e].vertexID;
                vertexList[e].vertexID = temp;
            }
        }
    }

    for(int i=0;i<arcNum;i++) {
        addArc(arcs[i].fromVertex,arcs[i].toVertex,arcs[i].weight);
    }
}

template <class T1,class T2>
void ListGraph<T1,T2>::addArc(T1 fromVertexID, T1 toVerTexID, T2 weight) {
    int fromVertex=0,toVerTex=0;
    for(int i=0;i<this->vertexNum;i++) {
        if (vertexList[i].vertexID == toVerTexID)
            toVerTex = i;
        if (vertexList[i].vertexID == fromVertexID)
            fromVertex = i;
    }
    Arc<T1,T2> *newArc = new Arc<T1,T2>(toVerTex,weight);
    if(this->vertexList[fromVertex].next==NULL) {
        this->vertexList[fromVertex].next = newArc;
    }
    else{
        Arc<T1,T2> *temp = this->vertexList[fromVertex].next;
        while(temp->nextArc != NULL)
            temp = temp->nextArc;
        temp->nextArc = newArc;
    }
}

template <class T1,class T2>
bool ListGraph<T1,T2>::getArc(T1 fromVertexID, T1 &toVertexID, T2 &weight) {
    if(vertexList[fromVertexID].next == NULL)
        return false;
    else{
        Arc<T1,T2> *temp = this->vertexList[fromVertexID].next;
        while(temp!=NULL && temp->visit){
            temp = temp->nextArc;
        }
        if(temp!=NULL){
            toVertexID = temp->toVertexID;
            weight = temp->weight;
            temp->visit = true;
            return true;
        }
        else
            return false;
    }
}

template <class T1,class T2>
void ListGraph<T1,T2>::print(){
    for(int i=0;i<this->vertexNum;i++) {
        cout<<(T1)vertexList[i].vertexID<<"|";
        Arc<T1,T2> *temp = vertexList[i].next;
        while(temp!=NULL){
            cout<<"->"<<(T1)(temp->toVertexID+'0')<<"|"<<(T2)temp->weight<<"|";
            temp = temp->nextArc;
        }
        cout<<"/"<<endl;
    }
}

template <class T1,class T2>
void ListGraph<T1,T2>::clearFlag() {
    for(int i=0;i<this->vertexNum;i++) {
        if(vertexList[i].next!=NULL){
            Arc<T1,T2> *temp = vertexList[i].next;
            while(temp!=NULL)
            {
                temp->visit = false;
                temp = temp->nextArc;
            }
        }
    }
}
template <class T1,class T2>
void ListGraph<T1,T2>::clearFlag(T1 index) {
    for(int i=0;i<this->vertexNum;i++) {
        if(i==index)
            continue;
        if(vertexList[i].next!=NULL){
            Arc<T1,T2> *temp = vertexList[i].next;
            while(temp!=NULL)
            {
                temp->visit = false;
                temp = temp->nextArc;
            }
        }
    }
}

template <class T1,class T2>
T1 ListGraph<T1,T2>::getID(T1 index) {
    return vertexList[index].vertexID;
}



#endif //GRAPH_LISTGRAPH_H
