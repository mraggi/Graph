#include "MinSpanningTree.hpp"
#include <queue>

using Edge = Graph::Edge;
using vertex_t = Graph::vertex_t;

struct by_reverse_weight
{
    bool operator()(const Edge& a, const Edge& b)
    {
        return a.weight() > b.weight();
    }
};

std::vector<Graph::Edge> minimum_spanning_tree(const Graph& G)
{
	auto n = G.num_vertices();
		
    std::vector<Edge> T;
	if (n == 0)
		return T;
	T.reserve(n);
	
    std::vector<char> explored(n,0);
	
    std::priority_queue<Edge,std::vector<Edge>,by_reverse_weight> EdgesToExplore;
	
	explored[0] = true;
	
	for (auto v : G.neighbors(0))
	{
		EdgesToExplore.push(Edge(0,v,v.weight()));
	}

    while (!EdgesToExplore.empty())
    {
        Edge s = EdgesToExplore.top();
		EdgesToExplore.pop();
		
		if (explored[s.to])
			continue;
		
		T.emplace_back(s.from,s.to,s.weight());
		explored[s.to] = true;
		for (auto v : G.neighbors(s.to))
		{
			if (explored[v] == 0)
				EdgesToExplore.push( Edge(s.to,v,v.weight()) );
		}
    }
    return T;
}
