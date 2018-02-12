#include "CommonGraphs.hpp"
#include "Probability.hpp"

namespace graphs
{

Graph Petersen()
{
	Graph G(10);

	G.add_edges({{0, 1},
				 {0, 4},
				 {0, 5},
				 {1, 2},
				 {1, 6},
				 {2, 3},
				 {2, 7},
				 {3, 4},
				 {3, 8},
				 {4, 9},
				 {5, 7},
				 {5, 8},
				 {6, 8},
				 {6, 9},
				 {7, 9}});

	G.sort_neighbors();

	return G;
}

Graph Path(int n)
{
	Graph G(n + 1);
	for (Graph::vertex_t i = 0; i < n; ++i)
		G.add_edge(i, i + 1);
	return G;
}

Graph Cycle(int n);

Graph Complete(int n);

Graph CompleteBipartite(int n, int m);

Graph RandomGraph(int n, double p)
{
	Graph G(n);

	for (auto i : G.vertices())
	{
		for (int j = i + 1; j < G.num_vertices(); ++j)
		{
			if (probability_of_true(p))
				G.add_edge(i, j);
		}
	}
	return G;
}

Graph RandomWeightedGraph(int n, double p)
{
	Graph G(n);

	for (auto i : G.vertices())
	{
		for (int j = i + 1; j < G.num_vertices(); ++j)
		{
			if (probability_of_true(p))
			{
				G.add_edge(i, j, random_int(0, 100));
			}
		}
	}
	return G;
}

// Fill here the cycle, path, complete and random graph.
}
