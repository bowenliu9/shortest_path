#include "Graph.h"
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <utility>

#define INF 1000000

using namespace std;

Graph::Graph() { // Default constructor
	// Since the mainlist and adj_list are both vectors, 
	// and each vertex and edge are added through other functions and not here,
	// there is no need to declare them in the constructor
	V = 0; // size of main_list
}

Graph::~Graph() {
	// First delete vector that stores the adjacent 
	// Then delete the main list
	for (int i = 0; i < main_list.size(); i++) {
		if (main_list[i].head != nullptr) {
			main_list[i].head->clear();
		}
	}
	main_list.clear();
}

void Graph::addVertex(string label) {
	// Pre-condition: 
	//		- stirng label is the vertex in the graph
	//		- label must be unique
	// Post-condition: 
	//		- label is added to the main_list as a struct along with a adj_element pointer
	main_element element;
	vector<adj_element>* adj_vect = new vector<adj_element>;
	element.head = adj_vect;
	element.vertex = label;
	main_list.push_back(element);
	V++;
}

void Graph::removeVertex(string label) {
	// Pre-condition:
	//		- stirng label is the vertex in the graph
	//		- label must exist in the graph
	// Post-condition:
	//		- vertex of label is removed from the main list
	//		- edges of label stored in adj_vect are also removed
	unsigned int vertex_index;
	for (unsigned int i = 0; i < main_list.size(); i++) {
		// Remove all adj_vect's vertex label
		if (main_list[i].vertex == label) {
			// Save index that contains vertex in the main list
			vertex_index = i;
		}
		else {
			// Check all other adj_vect for vertex label and remove it
			for (unsigned int j = 0; j < main_list[i].head->size(); j++) {
				if (main_list[i].head->operator[](j).vertex == label) {
					main_list[i].head->erase(main_list[i].head->begin() + j);
				}
			}
		}
	}
	main_list[vertex_index].head->clear(); // Remove adj_vect of main_list
	main_list.erase(main_list.begin() + vertex_index); // Remove vertex label from main_list
	V--;
}

void Graph::addEdge(string label1, string label2, unsigned long weight) {
	// Pre-condition:
	//		- stirng label1 and label2 are two of the vertices in the graph that will be connected
	//		- stirng label1 and label2 both must exist
	//		- unsigned long weight is the cost of the edge
	// Post-condition:
	//		- a struct containing label1 and the weight is added to label2's adj_vect and vice versa 
	for (unsigned int i = 0; i < main_list.size(); i++) {
		if (main_list[i].vertex == label1) {
			// Since adj_vector is already created for existing elements
			// Can just add adj elements 
			struct adj_element temp_element;
			temp_element.vertex = label2;
			temp_element.edge_weight = weight;
			main_list[i].head->push_back(temp_element);
		}
		if (main_list[i].vertex == label2) {
			struct adj_element temp_element;
			temp_element.vertex = label1;
			temp_element.edge_weight = weight;
			main_list[i].head->push_back(temp_element);
		}
	}
}

void Graph::removeEdge(string label1, string label2) {
	// Pre-condition:
	//		- stirng label1 and label2 are two of the vertices in the graph that will be removed
	//		- stirng label1 and label2 both must exist
	// Post-condition:
	//		- the struct containing label1 in label2's adj_vect is removed and vice versa 
	for (unsigned int i = 0; i < main_list.size(); i++) {
		if (main_list[i].vertex == label1) {
			// Found label1, remove its label2 from adj_vect
			for (unsigned int j = 0; j < main_list[i].head->size(); j++) {
				if (main_list[i].head->operator[](j).vertex == label2) {
					main_list[i].head->erase(main_list[i].head->begin() + j);
				}
			}
		}
		if (main_list[i].vertex == label2) {
			// Found label2, remove its label1 from adj_vect
			for (unsigned int j = 0; j < main_list[i].head->size(); j++) {
				if (main_list[i].head->operator[](j).vertex == label1) {
					main_list[i].head->erase(main_list[i].head->begin() + j);
				}
			}
		}
	}
}

void Graph::printGraph() {
	// Pre-condition:
	//		- Graph is not empty
	// Post-condition:
	//		- Graph is printed in order of the vertex being added
	//		- The adj_vect of each vertex is printed as well
	for (unsigned int i = 0; i < main_list.size(); i++) {
		cout << "Vertex: " << main_list[i].vertex << " ";
		for (unsigned int j = 0; j < main_list[i].head->size(); j++) {
			cout << "(" << main_list[i].head->operator[](j).vertex
				<< ", " << main_list[i].head->operator[](j).edge_weight << ")";
		}
		cout << endl;
	}
	cout << endl;
}

unsigned long Graph::shortestPath (string startLabel, string endLabel) {
	// Pre-condition:
	//		- string startLabel and endLabel are the starting and ending vertices of the path 
	//		- startLabel and endLabel must exist and be connected
	// Post-condition:
	//		- the smallest cost of every vertex from startLabel are printed
	//		- the path from startLabel to endLabel is printed
	//		- the smallest cost from startLabel and endLabel is returned

	// Store vertices
	// Extract shortest path
	// string for label, unsigned long for weight
	int s = getIndex(startLabel);
	int e = getIndex(endLabel);
	set<pair<int, int>> extract_set;  // entry_label's index and distance

	// Vector for storing distances from entry_label to every label
	vector<int> distances(V, INF);

	// Vector for storing parent of each vertex
	vector<int> parents(V, -1);

	// Insert entry point label, first distance is 0
	extract_set.insert(make_pair(0,s));
	distances[s] = 0;

	// Loop through until all shortest distances are set
	while (!extract_set.empty()) {
		// Since set stores like BST, the first is the smallest
		// Extract smallest 
		pair<int, int> temp = *(extract_set.begin()); // Save smallest in temp
		extract_set.erase(extract_set.begin()); // Remove smallest

		// Get vertex index
		int u = temp.second;

		// Check adjacency list of current vertex's index
		for (auto i = main_list[u].head->begin(); i != main_list[u].head->end(); i++) {
			// Save each vertex index and edge weight of u's vertex
			int v = getIndex((*i).vertex); 
			int weight = (*i).edge_weight;

			// Check if there's a shorter path to v
			if (distances[v] > distances[u] + weight) {
				if (distances[v] != INF) {
					// Remove since we found closer way
					extract_set.erase(extract_set.find(make_pair(distances[v], v)));
				}

				// Update shorter path in distances
				distances[v] = distances[u] + weight;
				parents[v] = u;
				extract_set.insert(make_pair(distances[v], v));
			}
		}
	}
	// Print table of vertex, distance, and parent
	cout << endl << "-- Using Dijsktra --" << endl;
	cout << "Minimum distances from vertex: " << startLabel << endl << endl;
	for (int i = 0; i < V; i++) {
		cout << "Vertex: " << main_list[i].vertex << ", Shortest Distance to " << startLabel << ": " << distances[i] << endl;
	}
	
	// Print path from startLabel to endLabel
	cout << endl << "Path from " << main_list[s].vertex << " to " << main_list[e].vertex << ": ";
	printPath(parents, e);
	cout << endl;
	return distances[e];
}

void Graph::printPath(vector<int> parents, int end_index) {
	// Pre-condition: 
	//		- parents vector stored each vertex's smallest cost to its previous vertex to the startLabel
	//		- end_index is the last vertex of the path
	// Post-condition:
	//		- the path from startLabel to endLabel is printed

	// Recursively go through parents vector going from the end to the start
	// Print in order by printing after the recursive call 
	if (parents[end_index] == -1) {
		// Reached the start
		cout << main_list[end_index].vertex;
		return;
	}
	printPath(parents, parents[end_index]);
	cout << "->" << main_list[end_index].vertex;
}


int Graph::getIndex(string label) {
	// Pre-condition: 
	//		- string label is a vertex of the graph
	//		- label must exist in the graph
	// Post-condition:
	//		- the index of the vertex within the main_list is returned
	for (unsigned int vert_index = 0; vert_index < main_list.size(); vert_index++) {
		if (main_list[vert_index].vertex == label) {
			return vert_index;
		}
	}
	return -1; // if cannot find element in vector
}