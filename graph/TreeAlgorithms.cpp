#include "TreeAlgorithms.hpp"
#include "ConnectedComponents.hpp"

#include <stack>

bool is_tree(const Graph& G) { return G.num_edges() + 1 == G.num_vertices() && is_connected(G); }

using Vertex = Graph::Vertex;

std::vector<Vertex> set_root(const Graph& G, Vertex root)
{
	std::vector<Vertex> parent(G.num_vertices());
	
	parent[root] = Graph::INVALID_VERTEX;
	
	std::stack<Vertex> frontier;
	frontier.emplace(root);
	
	while (!frontier.empty())
	{
		auto p = frontier.top();
		frontier.pop();
		
		for (auto u : G.neighbors(p))
		{
			if (parent[p] == u)
				continue;
			parent[u] = p;
			frontier.emplace(u);
		}
	}
	return parent;
}
