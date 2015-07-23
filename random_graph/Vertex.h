#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <map>

using namespace std;

class Vertex
{
private:
    int label;
    map<int,int> edges;

public:
    Vertex(int lb);
    const int & getLabel() const;
    const map<int,int>& getEdges() const;
    void addEdge(int lb);
};

#endif
