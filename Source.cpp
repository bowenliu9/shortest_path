#include <iostream>
#include <vector>
#include "Graph.h"
#include <set>
#include <list>
#include <utility>

#define INF 1000000 

using namespace std;

int main() {
	
	// Testing functionality of add and remove edges and vertices
	cout << "**First test the functionality of adding and removing edges and vertices**" << endl;
	Graph graph;
	graph.addVertex("A");
	graph.addVertex("B");
	graph.addVertex("C");
	graph.addVertex("D");
	graph.addEdge("A", "D", 5);
	graph.printGraph();
	graph.removeVertex("A");
	cout << "Removed Vertex \"A\" " << endl;
	graph.printGraph();
	graph.addVertex("E");
	graph.addVertex("F");
	graph.addVertex("G");
	graph.addVertex("H");
	graph.addEdge("B", "D", 5);
	graph.addEdge("B", "C", 15);
	graph.addEdge("B", "G", 25);
	graph.addEdge("F", "G", 1);
	graph.printGraph();
	cout << "Removed Edge \"B\" and \"C\" " << endl;
	graph.removeEdge("B", "C");
	graph.printGraph();
	
	/*
	Testing Dijstra Algorithm from online with expected results
	Vertex   Distance from Source
	0                0
	1                4
	2                12
	3                19
	4                21
	5                11
	6                9
	7                8
	8                14
	This is the set up
		 "B" -- 8 -- "C" -- 7 -- "D" 
		/             |           | \
	   4              2           |  9
	  /               |           |   \ 
	"A"       ------ "I"         14   "E"
	  \      /        |           |   /
	   8    7         6           |  10 
 	    \  /          |           | /
		 "H" -- 1 -- "G" -- 2 -- "F"
	*/
	cout << "**Second test of online graph with Dijkstra**" << endl;
	Graph graph2;
	graph2.addVertex("A");
	graph2.addVertex("B");
	graph2.addVertex("C");
	graph2.addVertex("D");
	graph2.addVertex("E");
	graph2.addVertex("F");
	graph2.addVertex("G");
	graph2.addVertex("H");
	graph2.addVertex("I");
	graph2.addEdge("A", "B", 4);
	graph2.addEdge("A", "H", 8);
	graph2.addEdge("B", "C", 8);
	graph2.addEdge("B", "H", 11);
	graph2.addEdge("C", "I", 2);
	graph2.addEdge("C", "D", 7);
	graph2.addEdge("D", "E", 9);
	graph2.addEdge("D", "F", 14);
	graph2.addEdge("E", "F", 10);
	graph2.addEdge("F", "G", 2);
	graph2.addEdge("G", "I", 6);
	graph2.addEdge("G", "H", 1);
	graph2.addEdge("H", "I", 7);
	graph2.printGraph();
	cout << "Find shortest path from A to I" << endl;
	graph2.shortestPath("A", "E");
	cout << endl;

	// Another test of original path for "longer" but cheaper path
	/*
	Original graph purposely designed to test A to C
	Expected path A->B->D->C
		   "B"
		   /|\
		  1 |  3
		 /  |   \
	    "A" 1   "C"
		 \  |   /
          3 |  1
		   \| /
		   "D"
	*/
	cout << "**Third test of original graph with longer but cheaper path with Dijkstra**" << endl;
	Graph graph3;
	graph3.addVertex("A");
	graph3.addVertex("B");
	graph3.addVertex("C");
	graph3.addVertex("D");
	graph3.addEdge("A", "B", 1);
	graph3.addEdge("A", "D", 3);
	graph3.addEdge("B", "C", 3);
	graph3.addEdge("B", "D", 1);
	graph3.addEdge("C", "D", 1);
	
	graph3.shortestPath("A", "C");
}