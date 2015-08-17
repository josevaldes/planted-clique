#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <ctime>
#include <queue>
#include "Vertex.h"
#include "Random_Graph.h"

using namespace std;

double nextInt(double x)
{
    if((x-floor(x)) < 0.5)
    {
        return floor(x);
    }

    return ceil(x);
}

Random_Graph::Random_Graph(unsigned int n):n_vertices(n+1), k_vertices(0)
{
   vertices.reserve(n_vertices);
  // srand(time(0));
   
   planted_clique = new bool [n_vertices + 1];
   for(unsigned int i = 0; i < n_vertices + 1; ++i)
   {
       planted_clique[i] = false;
   }
   
   for(unsigned int i = 0; i < n_vertices; ++i)
   {
       vertices[i] = new Vertex(i);
   }

  
  // float one_percent = (float)n_vertices / 100;
  // float percent = one_percent;
  // float status = 1;
   for(unsigned int u = 1; u < n_vertices; ++u)
   {
       /* while (u >= percent)
        {
 	    cout << status << "% of random vertices done" << endl;
		   percent += one_percent;
		   ++status;
	}
*/
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
    cerr << "DESTRUCTOR\n";
    delete[] planted_clique;
    
    for(unsigned int i = 0; i <= n_vertices; ++i)
    {
        delete vertices[i];
    }
    
   // delete[] vertices;
}

const unsigned int & Random_Graph::get_n_vertices() const
{
    return n_vertices;
}

const unsigned int & Random_Graph::get_k_vertices() const
{
    return k_vertices;
}

const vector<Vertex*> & Random_Graph::getVertices() const
{
    return vertices;
}

int Random_Graph::getCmpErr(const vector<unsigned int> & possibleClique) const
{
    cerr << "Size of candidate "<< possibleClique.size()<<endl;
    cerr << "Size of plant " << k_vertices <<endl;
    int errors = 0;
  //  if(errors < 0)
   // {
     //   errors *= -1;
   // }

    for(unsigned int i = 0; i < possibleClique.size(); ++i)
    {
        if(!planted_clique[possibleClique[i]])
	{
            ++errors;
	}
    }

    int error_size = abs(int(possibleClique.size() - k_vertices));

    return errors + error_size;
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
    //srand(time(0));
    


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


    cout << "Clique planted in vertices:\n"; 
/*	float one_percent = (float)k_vertices / 100;
	float percent = one_percent;
	float status = 1;
*/
    for(unsigned int i = 0; i < k_vertices; ++i)
    {
        cout << "  v" << k_elem[i]<< endl;
		/*while (i >= percent)
		{
			cout << status << "% of planted cliques done" << endl;
			percent += one_percent;
			++status;
		}*/
        for(unsigned int j = i + 1; j < k_vertices; ++j)
	    {
            vertices[k_elem[i]]->addEdge(k_elem[j]);
	        vertices[k_elem[j]]->addEdge(k_elem[i]);
	    }
    }
    
}

void Random_Graph::clear()
{
    delete[] planted_clique;
    
    for(unsigned int i = 0; i <= n_vertices; ++i)
    {
	delete vertices[i];
    }
    
}

unsigned int Random_Graph::kuceraAlg()
{
    unsigned int errors = 0;
    vector<Vertex*> highest_degrees(n_vertices+1);
    for(unsigned int i = 0; i <= n_vertices; ++i)
    {
        highest_degrees[i] = vertices[i];
    }

	cerr << "Starting the sorting of vertices degree\n";
    sort(highest_degrees.begin(), highest_degrees.end(), degreeCmp());
	cerr << "Sorting done\n";
	//float one_percent = (float)k_vertices / 100;
	//float percent = one_percent;
	//float status = 1;
    for(unsigned int i = 0; i < k_vertices; ++i)
    {
		/*while (i >= percent)
		{
			cout << status << "% of kucera cliques done" << endl;
			percent += one_percent;
			++status;
		}*/
		
      cout << "   v" << highest_degrees[i]->label<<endl;
       int kucera_index = highest_degrees[i]->label;
       if(!planted_clique[kucera_index])
       {
           ++errors;
       }
    }
    cout << "Kucera algorithm has "<< errors << " wrong vertices\n";
    
    return errors;
}

void Random_Graph::LDR_Alg()
{
    vector<bool> aliveV(n_vertices + 1, true);
    vector<unsigned int> planted;
    priority_queue<Vertex, vector<Vertex>, degreeLessCmp> min_heap;
    unsigned int n_limit = n_vertices - 1;

   
    for(unsigned int i = 1; i <= n_vertices; ++i)
    {
        min_heap.push(*vertices[i]);
    }

   
   Vertex ite = min_heap.top();

   while(ite.getDegree() != n_limit)
   {
       min_heap.pop();
       aliveV[ite.getLabel()] = false;
       
       vector<unsigned int> v_neighs = ite.getNeighs();
       

       for(unsigned int i = 0; i < v_neighs.size(); ++i)
       {
	   if(aliveV[v_neighs[i]])
	   {
	      --vertices[v_neighs[i]]->degree;
	      min_heap.push(*vertices[v_neighs[i]]);
	   }
       }
       
       --n_limit;
           
       ite = min_heap.top();
       while(!aliveV[ite.getLabel()])
       {
	   min_heap.pop();
	   ite = min_heap.top();
       }
       
   }


   bool done = false;
   bool breaking = false;

   while(!done)
   {
       planted = ite.getNeighs();
       for(int i = 0; i < planted.size(); ++i)
       {
          if(!aliveV[planted[i]])
	  {
             planted.erase(planted.begin()+i);
	     --i;
	  }
       }

       for(int u = 0; u < planted.size(); ++u)
       {
           for(int v = u+1; v < planted.size(); ++v)
	   {
               if(!vertices[planted[u]]->isNeigh(planted[v]))
	       {
	           aliveV[ite.getLabel()] = false;
                   min_heap.pop();
		   ite = min_heap.top();
		   breaking = true;
		   break;
	       }
	   }

	   if(breaking)
	   {
              break;
	   }
       }

       if(breaking)
       {
           breaking = false;
       }

       else
       {
           done = true;
       }
   }

   planted.push_back(ite.getLabel());

   for(unsigned int k = 0; k < aliveV.size(); ++k)
   {
       if(!aliveV[k])
       {
           bool member = true;

	   for(unsigned int l = 0; l < planted.size();++l)
	   {
               if(!vertices[k]->isNeigh(planted[l]))
	       {
                   member = false;
		   break;
	       }
	   }

	   if(member)
	   {
               planted.push_back(k);
	   }
       }
   }

   cout << "Errors in planted clique: " << getCmpErr(planted) << endl;
}


void Random_Graph::LDDR_Alg()
{
    vector<bool> aliveV(n_vertices + 1, true);
    vector<unsigned int> planted;
    priority_queue<Vertex*, vector<Vertex*>, degreeCmp> min_heap;
    unsigned int n_limit = n_vertices - 1;

   
    for(unsigned int i = 1; i <= n_vertices; ++i)
    {
        min_heap.push(vertices[i]);
    }

   Vertex* ite = min_heap.top();

   while(ite->getDegree() != n_limit)
   {
       min_heap.pop();
       aliveV[ite->getLabel()] = false;
       
       vector<unsigned int> v_neighs = ite->getNeighs();
       

       for(unsigned int i = 0; i < v_neighs.size(); ++i)
       {
	   if(aliveV[v_neighs[i]])
	   {
	      --vertices[v_neighs[i]]->degree;
	      min_heap.push(vertices[v_neighs[i]]);
	   }
       }
       
       --n_limit;
           
       ite = min_heap.top();
       while(!aliveV[ite->getLabel()])
       {
	   min_heap.pop();
	   ite = min_heap.top();
       }
       
   }


   bool done = false;
   bool breaking = false;

   while(!done)
   {
       planted = ite->getNeighs();
       for(int i = 0; i < planted.size(); ++i)
       {
          if(!aliveV[planted[i]])
	  {
             planted.erase(planted.begin()+i);
	     --i;
	  }
       }

       for(int u = 0; u < planted.size(); ++u)
       {
           for(int v = u+1; v < planted.size(); ++v)
	   {
               if(!vertices[planted[u]]->isNeigh(planted[v]))
	       {
	           aliveV[ite->getLabel()] = false;
                   min_heap.pop();
		   ite = min_heap.top();
		   breaking = true;
		   break;
	       }
	   }

	   if(breaking)
	   {
              break;
	   }
       }

       if(breaking)
       {
           breaking = false;
       }

       else
       {
           done = true;
       }
   }

   planted.push_back(ite->getLabel());

   for(unsigned int k = 0; k < aliveV.size(); ++k)
   {
       if(!aliveV[k])
       {
           bool member = true;

	   for(unsigned int l = 0; l < planted.size();++l)
	   {
               if(!vertices[k]->isNeigh(planted[l]))
	       {
                   member = false;
		   break;
	       }
	   }

	   if(member)
	   {
               planted.push_back(k);
	   }
       }
   }

   cout << "Errors in planted clique: " << getCmpErr(planted) << endl;
}

void Random_Graph::DGGP_Alg()
{
     double num_vertices = n_vertices;
     double t = (0.003* log2 (num_vertices))/0.0086;
     cerr<< "t = "<< t << endl;

     cerr<< "t = "<< t << endl;
     vector<Vertex*> current_graph(n_vertices+1);
     for(unsigned int i = 0; i <= n_vertices; ++i)
     {
        current_graph[i] = vertices[i];
     }
    
     vector<bool> Si(n_vertices+1, false);
     double Si_cardinality = 0;
     queue<unsigned int> Si_indices;
    // srand(time(0));

     for(unsigned int i = 0; i < floor(t); ++i)
     {
	 cerr << "Size before S"<<i<< " selection: " <<current_graph.size()-1<<endl;
         for(unsigned int j = 1; j < current_graph.size(); ++j)
	 {   
             unsigned int alpha = rand() % 10000;
	     cerr << "Alpha = " << alpha <<endl;
	     if(alpha < 3728)
	     {
                 Si[current_graph[j]->getLabel()] = true;
		 ++Si_cardinality;
		 Si_indices.push(current_graph[j]->getLabel());
		 current_graph.erase(current_graph.begin()+j);
		 --j;
             }
	 }
         cerr << "Size after S"<<i<< " selection: " <<current_graph.size()-1<<endl;
         cerr << "Vertices in S"<<i<< ": " <<Si_cardinality<<endl;
         double min_neighs = (0.5 * Si_cardinality) + (0.72 *(0.5 * sqrt(Si_cardinality)));
         
	 cerr << "Minimum neighbors for V"<<i<<" = "<<min_neighs<<endl;
	 
	 //min_neighs = nextInt(min_neighs);

	// cerr << "Minimum neighbors for V"<<i<<" = "<<min_neighs<<endl;
         for(unsigned int k = 1; k < current_graph.size(); ++k)
	 {
             unsigned int Si_k_neighs = 0;
	     vector<unsigned int> k_neighs = current_graph[k]->getNeighs();
	     
	     for(unsigned int l = 0; l < k_neighs.size(); ++l)
	     {
                 if(Si[k_neighs[l]])
		 {
                     ++Si_k_neighs;
		 }
	     }

	     if(Si_k_neighs < min_neighs)
	     {
		 //cerr << "V" << current_graph[k]->getLabel() << " eliminated for lack S\n";
                 current_graph.erase(current_graph.begin()+k);
		 --k;
	     }
	 }

	 Si_cardinality = 0;
	 while(!Si_indices.empty())
	 {
             Si[Si_indices.front()] = false;
	     Si_indices.pop();
	 }


         cerr << "Size after selecting neighbors of S"<<i<< " selection: " <<current_graph.size()-1<<endl;
     }

     cerr << "After first phase, size: " << current_graph.size()-1<<endl;
     double Kt = (pow(0.38455, t) * k_vertices);
     cerr << "Kt = " << Kt << endl;
     //Kt = nextInt(Kt);
    // cerr << "Kt = " << Kt << endl;
     
     double min_k_neighs = 0.75 * Kt;
     cerr << "3/4 of Kt = " << min_k_neighs<<endl;
     //min_k_neighs = nextInt(min_k_neighs);
    // cerr << "3/4 of Kt = " << min_k_neighs<<endl;
     
     sort(current_graph.begin()+1, current_graph.end(), degreeCmp());
     vector<bool> K_prime (n_vertices+1, false);
     vector<bool> K_final (n_vertices+1, false);

     for(unsigned int i = 0; i < Kt; ++i)
     {
         K_prime[current_graph[i+1]->getLabel()] = true;
     }

     for(unsigned int j = 1; j < current_graph.size(); ++j)
     {
         unsigned int K_prime_j_neighs = 0;
	 vector<unsigned int> j_neighs = current_graph[j]->getNeighs();
	 
	 for(unsigned int k = 0; k < j_neighs.size(); ++k)
	 {
             if(K_prime[j_neighs[k]])
	     {
                 ++K_prime_j_neighs;
	     }

	 }

	 if(K_prime_j_neighs < min_k_neighs)
	 {
	     current_graph.erase(current_graph.begin()+j);
	     --j;
	 }

	 else
	 {
             K_final[current_graph[j]->getLabel()] = true;
	 }
     }

     cerr << "After second phase, size: " << current_graph.size()-1<<endl;
     unsigned int K_prime_cardinality = current_graph.size() - 1;

     for(unsigned int u = 1; u <= n_vertices; ++u)
     {
         if(K_final[vertices[u]->getLabel()])
	 {

	 }
	 else if(vertices[u]->getDegree() >= K_prime_cardinality)
	 {
             int positive_hits = 0;
	     vector<unsigned int> u_neighs = vertices[u]->getNeighs();

	     for(unsigned int v = 0; v < u_neighs.size(); ++v)
	     {
                if(positive_hits == K_prime_cardinality)
		{
                    break;
		}

		if(K_final[u_neighs[v]])
		{
                    ++positive_hits;
		}
	     }

	     if(positive_hits == K_prime_cardinality)
	     {
                 current_graph.push_back(vertices[u]);
	     }
	 }
     }

     sort(current_graph.begin()+1, current_graph.end(), degreeCmp());
     vector<unsigned int> candidate_plant(k_vertices);

     cerr << "Candidates are: \n";
     for(unsigned int i = 0; i < k_vertices;++i)
     {
         candidate_plant[i] = current_graph[i+1]->getLabel();
	 cerr << candidate_plant[i]<<endl;;
     }
     
     cerr << "After third phase, size: " << current_graph.size()-1<<endl;
     //int errors = 0;

     
     int errors = getCmpErr(candidate_plant);
     /*
     int errors = int(k_vertices - current_graph.size() - 1);
     if(errors + 1 < 0)
     {
        cerr << "No error on size\n";
	errors *= -1;
     }
    
     for(unsigned int i = 1; i < current_graph.size(); ++i)
     {
         if(!planted_clique[current_graph[i]->getLabel()])
	 {
             ++errors;
	 }
     }*/

     cout << "DGGP Algorithm have "<< errors << " wrong vertices\n";

}
