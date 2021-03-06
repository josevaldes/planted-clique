#include <iostream>
#include <string>
#include <sstream>
#include "Random_Graph.h"
#include "Planted_Algorithms.h"

using namespace std;

int main(int argc, char* argv[])
{
   if(argc < 2 || argc > 3)
   {
       cerr << "Number of parameters incorrect. Enter number of vertices ";
       cerr << "as first parameter, and optionally, the size of a planted ";
       cerr << "clique as second parameter\n";
       return -1;
   }

   string input = argv[1];
   int number_vertices = 0;
   int planted_vertices = 0;
   
   stringstream myStream(argv[1]);
   if (myStream >> number_vertices && number_vertices > 0)
   {
       if(argc == 3)
       {
           stringstream mySStream(argv[2]);
	   
	   if(mySStream >> planted_vertices && planted_vertices > 0)
	   {
           }

	   else
	   {
               cerr << "Second argument format is incorrect. Restart program\n";
	       return -1;
	   }
       }
   }

   else
   {
       cerr << "First argument format is incorrect. Restart program\n";
       return -1;
   }

   cerr << "Creating random graph\n";
   Random_Graph G = Random_Graph(number_vertices);
  // Random_Graph GG = G;

   if(planted_vertices > 0)
   {
	   cerr << "Planting Cliques\n";
       G.plantClique(planted_vertices);
   }
   
 // G.displayAdjacencyList();
  // G.customIteration();
   cerr << "Starting LDR algorithm\n";

  // G.kuceraAlg();
   G.LDDR_Alg();

   //GG.kuceraAlg();
   
   return 0;
}
