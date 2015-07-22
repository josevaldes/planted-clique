#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include "Vertex.h"
#include "Random_Graph.h"

using namespace std;

Random_Graph::Random_Graph(int n):n_vertices(n)
{
   vertices = new Vertex*[n_vertices];
   srand(time(0));
   
   for(int i = 0; i < n_vertices; ++i)
   {
       vertices[i] = new Vertex(i);
   }

   for(int u = 0; u < n_vertices; ++u)
   {
       for(int v = u + 1; v < n_vertices; ++v)
       {
	   int indicator = rand() % 2;
	   
           if(indicator)
           {
               vertices[u]->addEdge(v);
	       vertices[v]->addEdge(u);
           }
       }
   }
}

void Random_Graph::displayAdjacencyList()
{
    cout << "Adjacency List\n";

    for(int i = 0; i < n_vertices; ++i)
    {
        cout << "Vertex " << i <<":\n";

	vector<int> currEdges = vertices[i]->getEdges();

	for(unsigned int j = 0; j < currEdges.size(); ++j)
	{
            cout << "   v"<< currEdges[j]<<endl;
	}
    }
}
