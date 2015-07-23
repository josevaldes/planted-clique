#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <ctime>
#include "Vertex.h"
#include "Random_Graph.h"

using namespace std;

Random_Graph::Random_Graph(int n):n_vertices(n+1)
{
   vertices = new Vertex*[n_vertices];
   srand(time(0));
   
   for(int i = 0; i < n_vertices; ++i)
   {
       vertices[i] = new Vertex(i);
   }

   for(int u = 1; u < n_vertices; ++u)
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

    for(int i = 1; i < n_vertices; ++i)
    {
        cout << "Vertex " << i <<":\n";

	map<int,int> currEdges = vertices[i]->getEdges();

	for(map<int,int>::iterator it = currEdges.begin(); it != currEdges.end(); ++it)
	{
            cout << "   v"<< it->first<<endl;
	}
    }
}

void Random_Graph::customIteration()
{
    bool quit = false;
    int iterator = 1;
    int temp = 1;
    string input = "";

    cout << "Move around the graph as you like. Enter the number of the vertex you want to go next.\n";
    cout << "To quit, press q and enter\n\n";
    
    while(!quit)
    {
       cout<< "Current vertex: " << iterator <<endl;
       cout<< "Adjacent vertices: "<<endl;
       
       map<int,int> currEdges = vertices[iterator]->getEdges();
       for(map<int,int>::iterator it = currEdges.begin(); it != currEdges.end(); ++it)
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
