#include <iostream>
#include <vector>
#include "Vertex.h"

using namespace std;

Vertex::Vertex(int lb):label(lb)
{
}

int Vertex::getLabel() const
{
    return label;
}

vector<int> Vertex::getEdges() const
{
    return edges;
}

void Vertex::addEdge(int lb)
{
    edges.push_back(lb);
}
