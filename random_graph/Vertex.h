#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <map>

using namespace std;

class Vertex
{
private:
    unsigned int label;
    unsigned int degree;
    map<unsigned int,unsigned int> edges;

public:
    Vertex(unsigned int lb);
    const unsigned int & getLabel() const;
    const map<unsigned int,unsigned int>& getEdges() const;
    void addEdge(unsigned int lb);
};

#endif
