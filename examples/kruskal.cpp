/*
This example program uses the equivalence relation library to implement
Kruskal's greedy minimum spanning tree algorithm.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <equiv_relation>

struct edge
{
	unsigned v1,v2;
	double weight;
};

int main()
{
	// Original graph, plus the minimal spanning tree.
	std::vector<edge> graph, mst;
	unsigned num_vertices = 0;
	
	// Read the file
	{
		std::ifstream infile("graph.txt");
		
		// Each line is in the format <v1> <v2> <weight>
		edge e;
		while(infile >> e.v1 >> e.v2 >> e.weight)
		{
			graph.emplace_back(e);
			
			// The number of vertices can be determined dynamically by
			// finding the largest vertex number read. Indexed from 0, so
			// num_vertices should always be larger than the valid indexes.
			if (num_vertices <= e.v1) num_vertices = e.v1 + 1;
			if (num_vertices <= e.v2) num_vertices = e.v2 + 1;
		}
	}
	
	// Sort the edges by weight in non-descending order
	std::sort(graph.begin(),graph.end(),[](const edge& e1, const edge& e2)
	{
		return e1.weight < e2.weight;
	});
	
	// Greedily add the lightest edges as long as the given vertices do not
	// already have a path between them.
	cpeq::eq_relation connections(num_vertices);
	
	for (const edge& e : graph)
	{
		if (!connections.equivalent(e.v1,e.v2))
		{
			connections.merge(e.v1,e.v2);
			mst.emplace_back(e);
		}
	}
	
	// Print the edges in the MST
	for (const edge& e : mst)
	{
		std::cout << e.v1 << ' ' << e.v2 << ' ' << e.weight << '\n';
	}
}
