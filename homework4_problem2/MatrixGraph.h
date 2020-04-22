//
// Created by Blue Sky on 4/15/20.
//

#ifndef GRAPH_MATRIXGRAPH_H
#define GRAPH_MATRIXGRAPH_H

#include "Graph.h"
template <class T1,class T2>
class MatrixGraph:public Graph<T1,T2>{
private:
    T1 **graph;
    T1 *index;
    bool **visit;
public:
    MatrixGraph(int vertexNum,int arcNum,Edge<T1,T2> *arcs);
    void addArc(T1 fromVertexID,T1 toVerTexID,T2 weight);
    bool getArc(T1 fromVertexID,T1 &toVertexID,T2 &weight);
    void clearFlag();
    void clearFlag(T1 index);
    void print();
    T1 getID(T1 index);
};

template <class T1,class T2>
MatrixGraph<T1,T2>::MatrixGraph(int vertexNum,int arcNum,Edge<T1,T2> *arcs):Graph<T1,T2>(vertexNum,arcNum) {
    this->vertexNum = vertexNum;
    graph = (T1 **)malloc(vertexNum*sizeof(T1*));
    index = (T1 *)malloc(vertexNum*sizeof(T1));
    visit = (bool **)malloc(vertexNum*sizeof(bool*));
    for(int i=0;i<vertexNum;i++) {
        graph[i] = (T1 *) malloc(vertexNum*sizeof(T1));
        visit[i] = (bool *)malloc(vertexNum*sizeof(bool));
        index[i] = -1;
    }
    for(int i=0;i<this->vertexNum;i++)
        for(int e=0;e<this->vertexNum;e++) {
            graph[i][e] = 0;
            visit[i][e] = false;
        }
    for(int i=0;i<arcNum;i++)
    {
        bool flag1 = true,flag2 = true;
        int e;
        for(e=0;e<vertexNum&&index[e]!=-1;e++){
            if(arcs[i].fromVertex == index[e])
                flag1 = false;
            if(arcs[i].toVertex == index[e])
                flag2 = false;
        }
        if(flag1) {
            index[e]= arcs[i].fromVertex;
            e++;
        }
        if(flag2)
            index[e] = arcs[i].toVertex;
    }
    for(int i=0;i<vertexNum;i++)
    {
        for(int e=i;e<vertexNum;e++){
            if(index[i]>index[e]) {
                T1 temp = index[i];
                index[i] = index[e];
                index[e] = temp;
            }
        }
    }
    for(int i=0;i<arcNum;i++) {
        addArc(arcs[i].fromVertex,arcs[i].toVertex,arcs[i].weight);
    }
}

template <class T1,class T2>
void MatrixGraph<T1,T2>::addArc(T1 fromVertexID, T1 toVerTexID, T2 weight) {
    int fromVertex=0,toVertex=0;
    for(int i=0;i<this->vertexNum;i++)
    {
        if(fromVertexID==index[i])
            fromVertex = i;
        if(toVerTexID==index[i])
            toVertex = i;
    }
    graph[fromVertex][toVertex] = weight;
}

template <class T1,class T2>
bool MatrixGraph<T1,T2>::getArc(T1 fromVertexID, T1 &toVertexID, T2 &weight) {
    for(int i=0;i<this->vertexNum;i++){
        if(graph[fromVertexID][i]!=0 && !visit[fromVertexID][i] )
        {
            toVertexID = i;
            weight = graph[fromVertexID][i];
            visit[fromVertexID][i] = true;
            return true;
        }
    }
    return false;
}

template <class T1,class T2>
void MatrixGraph<T1,T2>::print(){
    for(int i=0;i<this->vertexNum;i++){
        for(int e=0;e<this->vertexNum;e++)
        {
            stringstream ss;
            ss << (double)graph[i][e];
            cout<<ss.str()<<" ";
        }
        cout<<endl;
    }
}

template <class T1,class T2>
void MatrixGraph<T1,T2>::clearFlag(){
    for(int i=0;i<this->vertexNum;i++)
    {
        for(int e=0;e<this->vertexNum;e++)
            visit[i][e] = false;
    }
}

template <class T1,class T2>
void MatrixGraph<T1,T2>::clearFlag(T1 index){
    for(int i=0;i<this->vertexNum;i++)
    {
        if(i==index)
            continue;
        for(int e=0;e<this->vertexNum;e++)
            visit[i][e] = false;

    }
}

template <class T1,class T2>
T1 MatrixGraph<T1,T2>::getID(T1 index) {
    return this->index[index];
}
#endif //GRAPH_MATRIXGRAPH_H
