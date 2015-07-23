#include <iostream>
#include <string>
#include <sstream>
#include "Random_Graph.h"

using namespace std;

int main()
{
   string input = "";
   int number_vertices = 0;
   while(true)
   {
       cout << "Enter the number of vertices for this graph: ";
       getline(cin, input);

       stringstream myStream(input);
       if (myStream >> number_vertices && number_vertices > 0)
       {
           break;
       }

       cerr << "Invalid number, please try again\n";
   }

   Random_Graph G = Random_Graph(number_vertices);
   G.customIteration();
   return 0;
}
