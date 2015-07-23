#ifndef RANDOM_GRAPH_H
#define RANDOM_GRAPH_H

#include <iostream>
#include <vector>
#include "Vertex.h"

using namespace std;

class Random_Graph
{
private:
    int n_vertices;
    Vertex** vertices;

public:
    Random_Graph(int n);
    void displayAdjacencyList();
    void customIteration();
};

#endif
