#include <algorithm>
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

   float one_percent = (float)n_vertices / 100;
   float percent = one_percent;
   float status = 1;
   for(unsigned int u = 1; u < n_vertices; ++u)
   {
        while (u >= percent)
        {
 	    cout << status << "% of random vertices done" << endl;
		   percent += one_percent;
		   ++status;
	}

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

Random_Graph::~Random_Graph()
{
    delete[] planted_clique;
    
    for(unsigned int i = 0; i <= n_vertices; ++i)
    {
        delete vertices[i];
    }
    
    delete[] vertices;
}

void Random_Graph::displayAdjacencyList()
{
    cout << "Adjacency List\n";

    for(unsigned int i = 1; i <= n_vertices; ++i)
    {
        cout << "Vertex " << i <<":\n";
	cout << "Degree: " << vertices[i]->degree << endl;


	for(map<unsigned int,unsigned int>::iterator it = vertices[i]->edges.begin(); it != vertices[i]->edges.end(); ++it)
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
       cout << "Degree: " << vertices[iterator]->degree << endl;
       cout<< "Adjacent vertices: "<<endl;
      
       for(map<unsigned int,unsigned int>::iterator it = vertices[iterator]->edges.begin(); it != vertices[iterator]->edges.end(); ++it)
       {
           if(it->second != 0)
	   {
	       cout << "   v"<< it->first<<endl;
	   }
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
	   
       if(vertices[iterator]->edges[temp] == 0)
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
    
    planted_clique = new bool [n_vertices + 1];
    for(unsigned int i = 0; i < n_vertices + 1; ++i)
    {
        planted_clique[i] = false;
    }

    vector<unsigned int> k_elem(k);

    while(k_vertices < k)
    {
        unsigned int index = (rand() % n_vertices) + 1;
	
	if(!planted_clique[index])
	{
	    k_elem[k_vertices] = index;
            ++k_vertices;
	    planted_clique[index] = true;
	}

    }


    //cout << "Clique planted in vertices:\n"; 
	float one_percent = (float)k_vertices / 100;
	float percent = one_percent;
	float status = 1;

    for(unsigned int i = 0; i < k_vertices; ++i)
    {
       // cout << "  v" << k_elem[i]<< endl;
		while (i >= percent)
		{
			cout << status << "% of planted cliques done" << endl;
			percent += one_percent;
			++status;
		}
        for(unsigned int j = i + 1; j < k_vertices; ++j)
	    {
            vertices[k_elem[i]]->addEdge(k_elem[j]);
	        vertices[k_elem[j]]->addEdge(k_elem[i]);
	    }
    }
    
}

void Random_Graph::kuceraAlg()
{
    unsigned int errors = 0;
    vector<Vertex*> highest_degrees(n_vertices);
    for(unsigned int i = 0; i <= n_vertices; ++i)
    {
        highest_degrees[i] = vertices[i];
    }

	cerr << "Starting the sorting of vertices degree\n";
    sort(highest_degrees.begin(), highest_degrees.end(), degreeCmp());
	cerr << "Sorting done\n";
	float one_percent = (float)k_vertices / 100;
	float percent = one_percent;
	float status = 1;
    for(unsigned int i = 0; i < k_vertices; ++i)
    {
		while (i >= percent)
		{
			cout << status << "% of kucera cliques done" << endl;
			percent += one_percent;
			++status;
		}
		
      // cout << "   v" << highest_degrees[i]->label<<endl;
       int kucera_index = highest_degrees[i]->label;
       if(!planted_clique[kucera_index])
       {
           ++errors;
       }
    }
    cout << "Kucera algorithm has "<< errors << " wrong vertices\n";
}

