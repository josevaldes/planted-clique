#include <iostream>
#include <map>
#include "Vertex.h"

using namespace std;

Vertex::Vertex(int lb):label(lb)
{
}

const int& Vertex::getLabel() const
{
    return label;
}

const map<int,int>& Vertex::getEdges() const
{
    return edges;
}

void Vertex::addEdge(int lb)
{
    edges[lb] = lb;
}
