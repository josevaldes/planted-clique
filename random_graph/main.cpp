#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "Random_Graph.h"

using namespace std;

int main(int argc, char* argv[])
{
   srand(time(0));
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

   float successes = 0;
   float avg_error = 0;
   
   for(int i = 0; i < 1000; ++i)
   {
       cerr << "Creating random graph\n";
       Random_Graph G = Random_Graph(number_vertices);
      // Random_Graph GG = G;

       if(planted_vertices > 0)
       {
	   cerr << "Planting Cliques\n";
           G.plantClique(planted_vertices);
       }
   
    //   G.displayAdjacencyList();
    // G.customIteration();
    // cerr << "Starting LCD algorithm\n";

       cerr << "Starting Kucera algorithm\n";
       unsigned int trial = G.kuceraAlg(); 
       if(trial == 0)
       {
           ++successes;
       }

       else
       {
           avg_error += trial;
       }

    // G.LDDR_Alg();
      
    //GG.kuceraAlg();
    
   // G.DGGP_Alg();
   }

   cout << "Success probability: " << successes / 1000 <<endl;
   
   cout << "Total errors: " << avg_error << endl;
   cout << "Average errors: " << avg_error / 1000 << endl;
   return 0;
}
