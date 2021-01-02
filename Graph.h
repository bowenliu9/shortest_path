#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct main_element {
	// Store each vertex for the main list
	string vertex;
	vector<struct adj_element>* head;
};

struct adj_element {
	// Store each vertex and weight for the adjacency list
	string vertex;
	unsigned long edge_weight;
};

class Graph
{
public:
	Graph();
	~Graph();
	void addVertex(string label);
	void removeVertex(string label);
	void addEdge(string label1, string label2, unsigned long weight);
	void removeEdge(string label1, string label2);
	void printGraph();
	unsigned long shortestPath(string startLabel, string endLabel);
private:
	vector<main_element> main_list;
	int V;
	int getIndex(string label);
	void printPath(vector<int> parents, int end_index);
};

