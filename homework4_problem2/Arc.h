//
// Created by Blue Sky on 4/15/20.
//

#ifndef GRAPH_ARC_H
#define GRAPH_ARC_H

#include <iostream>
template<class T1,class T2>
class Arc{
public:
    T1 toVertexID;
    T2 weight;
    Arc *nextArc;
    bool visit;
    Arc(T1 toVertexID,T2 weight);
};

template <class T1,class T2>
Arc<T1,T2>::Arc(T1 toVertexID, T2 weight) {
    this->toVertexID = toVertexID;
    this->weight = weight;
    this->visit = false;
    this->nextArc = NULL;
}
#endif //GRAPH_ARC_H
