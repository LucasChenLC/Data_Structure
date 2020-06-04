//
// Created by Blue Sky on 4/15/20.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <climits>
#include "Vertex.h"
#include "Edge.h"
using namespace std;

template <typename T>
struct dijksraNode{
    T length;
    int pre;
};

template <class T1,class T2>
class Graph{
protected:
    int vertexNum;
    int arcNum;
    int originVertex;
    bool *flag;
    struct dijksraNode<T2> *dijksraList;

public:
    Graph(int vertexNum,int arcNum);
    void Dijksra(int originVertex);
    void DijksraPrint();
    void Prim();
    bool isLoop();
    bool check(T1 id,T1 checkIndex);
    virtual void addArc(T1 fromVertex,T1 toVerTex,T2 weight) = 0;
    virtual void clearFlag()=0;
    virtual void clearFlag(T1 index)=0;
    virtual bool getArc(T1 fromVertexID,T1 &toVertexID,T2 &weight) = 0;
    virtual T1 getID(T1 index) = 0;
    virtual void print() =0;
private:
    bool isFlagBlank();
    int findMin();
};

template <class T1,class T2>
Graph<T1,T2>::Graph(int vertexNum,int arcNum){
    this->vertexNum = vertexNum;
    this->arcNum = arcNum;
    flag = (bool *)malloc(vertexNum*sizeof(bool));
    dijksraList = (dijksraNode<T2> *)malloc(vertexNum*sizeof(dijksraNode<T2>));
    for(int i=0;i<vertexNum;i++) {
        flag[i] = false;
        dijksraList[i].length = 999;
    }
};

template <class T1,class T2>
void Graph<T1,T2>::Dijksra(int originVertex){
    T1 min,toVertexID;
    T2 weight,temp;
    this->originVertex = originVertex;
    for(int i=0;i<vertexNum;i++)
        dijksraList[i].pre = originVertex;
    dijksraList[originVertex].length = 0;
    while(!isFlagBlank()){
        min = findMin();
        flag[min] = true;
        while(getArc(min,toVertexID,weight)){
            temp = dijksraList[min].length + weight;
            if(temp<dijksraList[toVertexID].length){
                dijksraList[toVertexID].length = temp;
                dijksraList[toVertexID].pre = min;
            }
        }
    }
}

template <class T1,class T2>
void Graph<T1,T2>::DijksraPrint(){
    int temp;
    for(int i=0;i<vertexNum;i++){
        if(i!=originVertex){
            stack<int> path;
            cout<<originVertex<<"-"<<i<<" "<<dijksraList[i].length<<" ";
            if(dijksraList[i].length!=999) {
                temp = i;
                path.push(temp);
                while (dijksraList[temp].pre != originVertex) {
                    path.push(dijksraList[temp].pre);
                    temp = dijksraList[temp].pre;
                }
                cout << originVertex;
                while (!path.empty()) {
                    cout << "-" << path.top();
                    path.pop();
                }
            }
            else
                cout<<"-";
                cout << endl;

        }
    }
}

template <class T1,class T2>
bool Graph<T1,T2>::isFlagBlank(){
    for(int i=0;i<vertexNum;i++)
        if(!flag[i])
            return false;
    return true;
}

template <class T1,class T2>
int Graph<T1,T2>::findMin(){
    int min;
    for(int i=0;i<vertexNum;i++) {
        if(!flag[i])
        {
            min = i;
            break;
        }
    }
    for(int i=0;i<vertexNum;i++){
        if(!flag[i])
            if(dijksraList[i].length<dijksraList[min].length)
                min = i;
    }
    return min;
}

template <class T1,class T2>
void Graph<T1,T2>::Prim(){
    Edge<char,int> *arcs = (Edge<char,int> *)malloc(arcNum*sizeof(Edge<char,int>));
    int num=0;
    flag[0] = true;
    T1 toVertex,minVertex,minFromVertex;
    T2 weight,minWeight;
    while(!isFlagBlank()) {
        minWeight = CHAR_MAX;
        for(T1 i=0;i<vertexNum;i++){
            while(getArc(i,toVertex,weight)) {
                if((flag[toVertex]&&!flag[i])||(!flag[toVertex]&&flag[i]))
                    if (weight < minWeight) {
                            minFromVertex = i;
                            minWeight = weight;
                            minVertex = toVertex;
                    }
            }
        }
        arcs[num].weight = minWeight;
        arcs[num].toVertex = getID(minVertex);
        arcs[num].fromVertex = getID(minFromVertex);
        num++;
        if(!flag[minVertex])
            flag[minVertex] = true;
        else
            flag[minFromVertex] = true;
        clearFlag();
    }
    for(int i=0;i<num;i++)
        for(int e=i;e<num;e++){
            if(arcs[e]<arcs[i]){
                Edge<char,int> temp = arcs[e];
                arcs[e] = arcs[i];
                arcs[i] = temp;
            }
        }
    for(int i=0;i<num;i++){
        cout<<arcs[i].fromVertex<<"-"<<arcs[i].toVertex<<"-"<<arcs[i].weight<<endl;
    }
}

template <class T1,class T2>
bool Graph<T1,T2>::isLoop(){
    T1 toVertex,toVertexI;
    T2 weight;
    bool ans;
    for(T1 i=0;i<vertexNum;i++){
        while(getArc(i,toVertex,weight)){
            if(toVertex==i)
                return true;
            else
                if(check(toVertex,i))
                    return true;
            check(toVertex,weight);
            clearFlag(i);
        }
    }
    return false;
}

template <class T1,class T2>
bool Graph<T1,T2>::check(T1 id,T1 checkIndex){
    T1 toVertex;
    T2 weight;
    while(getArc(id,toVertex,weight)){
        if(toVertex==checkIndex)
            return true;
        else
            if(check(toVertex,checkIndex))
                return true;
    }
    return false;
}


#endif //GRAPH_GRAPH_H
