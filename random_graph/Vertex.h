#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <vector>

using namespace std;

class Vertex
{
private:
    int label;
    vector<int> edges;

public:
    Vertex(int lb);
    int getLabel() const;
    vector<int> getEdges() const;
    void addEdge(int lb);
};

#endif
