//
// Created by Blue Sky on 4/15/20.
//

#ifndef GRAPH_VERTEX_H
#define GRAPH_VERTEX_H
#include "Arc.h"

template <class T1,class T2>
class Vertex{
public:
    int vertexID;
    Arc<T1,T2> *next;
    Vertex();
    Vertex(T1 vertexID);
};

template <class T1,class T2>
Vertex<T1,T2>::Vertex() {
    this->next = NULL;
}

template <class T1,class T2>
Vertex<T1,T2>::Vertex(T1 vertexID) {
    this->vertexID = vertexID;
}
#endif //GRAPH_VERTEX_H
