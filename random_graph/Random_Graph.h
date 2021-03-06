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
    vector<Vertex*> vertices;
    bool* planted_clique;

public:
    Random_Graph(unsigned int n);
    const unsigned int & get_n_vertices() const;
    const unsigned int & get_k_vertices() const;
    const vector<Vertex*> & getVertices() const;
    unsigned int getCmpErr(const vector<unsigned int> & possibleClique) const;
    void displayAdjacencyList();
    void customIteration();
    void plantClique(unsigned int k);
    void kuceraAlg();
    void LDR_Alg();
    void LDDR_Alg();
    ~Random_Graph();
};



#endif
