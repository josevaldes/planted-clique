#include <iostream>
#include <map>
#include "Vertex.h"

using namespace std;

Vertex::Vertex(unsigned int lb):label(lb), degree(0)
{
}

const unsigned int& Vertex::getLabel() const
{
    return label;
}

const map<unsigned int,unsigned int>& Vertex::getEdges() const
{
    return edges;
}

void Vertex::addEdge(unsigned int lb)
{
    edges[lb] = lb;
    ++degree;
}
