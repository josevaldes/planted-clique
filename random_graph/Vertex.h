#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Random_Graph;

class Vertex
{
friend class Random_Graph;

private:
    unsigned int label;
    unsigned int degree;
    unsigned int constant_degree;
    map<unsigned int,unsigned int> edges;

public:
    Vertex(unsigned int lb);
    const unsigned int & getLabel() const;
    const unsigned int & getDegree() const;
    vector<unsigned int> getNeighs();
    bool isNeigh(unsigned int neigh);
    void addEdge(unsigned int lb);
};

class degreeCmp
{
public:
    bool operator()(Vertex * lhs, Vertex* rhs);
};

class degreeLessCmp
{
public:
    bool operator()(const Vertex & lhs, const Vertex & rhs);
};
#endif
