#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <ctime>
#include "Vertex.h"
#include "Random_Graph.h"

using namespace std;

Random_Graph::Random_Graph(unsigned int n):n_vertices(n+1), k_vertices(0)
{
   vertices = new Vertex*[n_vertices];
   srand(time(0));
   
   for(unsigned int i = 0; i < n_vertices; ++i)
   {
       vertices[i] = new Vertex(i);
   }

   for(unsigned int u = 1; u < n_vertices; ++u)
   {
       for(unsigned int v = u + 1; v < n_vertices; ++v)
       {
	   unsigned int indicator = rand() % 2;
	   
           if(indicator)
           {
               vertices[u]->addEdge(v);
	       vertices[v]->addEdge(u);
           }
       }
   }

   --n_vertices;
}

void Random_Graph::displayAdjacencyList()
{
    cout << "Adjacency List\n";

    for(unsigned int i = 1; i < n_vertices; ++i)
    {
        cout << "Vertex " << i <<":\n";

	map<unsigned int,unsigned int> currEdges = vertices[i]->getEdges();

	for(map<unsigned int,unsigned int>::iterator it = currEdges.begin(); it != currEdges.end(); ++it)
	{
            cout << "   v"<< it->first<<endl;
	}
    }
}

void Random_Graph::customIteration()
{
    bool quit = false;
    unsigned int iterator = 1;
    unsigned int temp = 1;
    string input = "";

    cout << "Move around the graph as you like. Enter the number of the vertex you want to go next.\n";
    cout << "To quit, press q and enter\n\n";
    
    while(!quit)
    {
       cout<< "Current vertex: " << iterator <<endl;
       cout<< "Adjacent vertices: "<<endl;
       
       map<unsigned int,unsigned int> currEdges = vertices[iterator]->getEdges();
       for(map<unsigned int,unsigned int>::iterator it = currEdges.begin(); it != currEdges.end(); ++it)
       {
           cout << "   v"<< it->first<<endl;
       }

       while(true)
       {
           cout << "Enter the vertex you want to traverse: ";
           getline(cin, input);
           stringstream myStream(input);
        
	   if(input == "q" || input == "Q")
	   {
               quit = true;
	   }

           if (myStream >> temp || quit)
           {
               break;
           }

           cerr << "Invalid number, please try again\n";

       }

       if(quit)
       {
           break;
       }
	   
       if(currEdges[temp] == 0)
       {
           cerr << "The vertex " << temp << " is not adjacent to current vertex"<<endl;
           cerr << "Pick again\n";
       }

       else
       {
           iterator = temp;
       }
    }
}

void Random_Graph::plantClique(unsigned int k)
{
    srand(time(0));
    
    bool indicators[n_vertices + 1];
    for(unsigned int i = 0; i < n_vertices + 1; ++i)
    {
        indicators[i] = false;
    }

    unsigned int k_elem[k];

    while(k_vertices < k)
    {
        unsigned int index = (rand() % n_vertices) + 1;
	
	if(!indicators[index])
	{
	    k_elem[k_vertices] = index;

            ++k_vertices;
	    indicators[index] = true;
	}

    }

    cout << "Clique planted in vertices:\n";
    
    for(unsigned int i = 0; i < k_vertices; ++i)
    {
        cout << "  v" << k_elem[i]<< endl;
    }
    
    for(unsigned int i = 0; i < k_vertices; ++i)
    {
        for(unsigned int j = i + 1; j < k_vertices; ++j)
	{
            vertices[k_elem[i]]->addEdge(k_elem[j]);
	    vertices[k_elem[j]]->addEdge(k_elem[i]);
	}
    }
    
}

