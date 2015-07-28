#ifndef RANDOM_GRAPH_H
#define RANDOM_GRAPH_H

#include <iostream>
#include <vector>
#include "Vertex.h"

using namespace std;

class Random_Graph
{
private:
    unsigned int n_vertices;
    unsigned int k_vertices;
    Vertex** vertices;
    Vertex** planted_clique;

public:
    Random_Graph(unsigned int n);
    void displayAdjacencyList();
    void customIteration();
    void plantClique(unsigned int k);
    void kuceraAlg();
};



#endif
