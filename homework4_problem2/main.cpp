#include <iostream>
#include <stack>
#include "Edge.h"
#include "ListGraph.h"
#include "MatrixGraph.h"

int main() {
    int vertexNum,arcNum;
    Edge<char,int> *edges;
    cin>>vertexNum>>arcNum;
    edges = (Edge<char,int>*)malloc(arcNum*sizeof(Edge<char,int>));
    for(int i=0;i<arcNum;i++)
        cin>>edges[i].fromVertex>>edges[i].toVertex>>edges[i].weight;
    Graph<char,int> *g;
    g =  new MatrixGraph<char,int>(vertexNum,arcNum,edges);
    //g = new ListGraph<char,int>(vertexNum,arcNum,edges);
    //g->print();
    //g->Dijksra(0);
   // g->DijksraPrint();
    g->Prim();
    //cout<<g->isLoop();
    return 0;
}
