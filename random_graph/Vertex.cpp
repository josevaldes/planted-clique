#include <iostream>
#include <map>
#include "Vertex.h"

using namespace std;

Vertex::Vertex(unsigned int lb):label(lb), degree(0), constant_degree(0)
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

vector<unsigned int> Vertex::getNeighs()
{
    vector<unsigned int> neighs(constant_degree);
    unsigned int i = 0;
    for(map<unsigned int,unsigned int>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
       if(it->second != 0)
       {
           neighs[i] = it->first;
	   ++i;
       }
    }

    return neighs;
}

bool Vertex::isNeigh(unsigned int neigh)
{
    return edges[neigh] != 0;
}
void Vertex::addEdge(unsigned int lb)
{
    if(edges[lb] == 0)
    {
        edges[lb] = lb;
        ++degree;
	constant_degree = degree;
    }
}

bool degreeCmp::operator()(Vertex* lhs, Vertex* rhs)
{
    if(lhs->getDegree() != rhs->getDegree())
    {
        return lhs->getDegree() > rhs->getDegree();
    }

    return lhs->getLabel() < rhs->getLabel();
}


bool degreeLessCmp::operator()(const Vertex & lhs, const Vertex & rhs)
{
    if(lhs.getDegree() != rhs.getDegree())
    {
        return lhs.getDegree() > rhs.getDegree();
    }

    return lhs.getLabel() > rhs.getLabel();
}
