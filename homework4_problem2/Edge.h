//
// Created by Blue Sky on 4/16/20.
//

#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

template <class T1,class T2>
class Edge{
public:
    T1 fromVertex;
    T1 toVertex;
    T2 weight;
    bool operator<(const Edge &otherEdge){
        if(this->fromVertex<otherEdge.fromVertex)
            return true;
        else if(this->fromVertex==otherEdge.fromVertex)
            if(this->toVertex<otherEdge.toVertex)
                return true;
            else
                return false;
        else
            return false;
    }
};
#endif //GRAPH_EDGE_H
