#include <iostream>
#include <map>
#include "Vertex.h"

using namespace std;

Vertex::Vertex(unsigned int lb):label(lb), degree(0)
{
}

const unsigned int & Vertex::getDegree() const 
{
    return degree;
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
    if(edges[lb] == 0)
    {
        edges[lb] = lb;
        ++degree;
    }
}

bool degreeCmp::operator()(Vertex* lhs, Vertex* rhs)
{
    return lhs->getDegree() > rhs->getDegree();
}
