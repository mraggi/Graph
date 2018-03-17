#include "ShortestPaths.hpp"

using Distance = Graph::sumweight_t;
using Vertex = Graph::Vertex;

const auto INF = std::numeric_limits<Distance>::max();

struct DummyPath
{
	Vertex last;
	Distance length;
};

inline bool operator<(const DummyPath& a, const DummyPath& b) { return a.length > b.length; }

std::vector<Distance> DijkstraCost(const Graph& G, Graph::Vertex origin, Graph::Vertex destination)
{
	std::vector<Distance> distance(G.num_vertices(), INF);
	distance[origin] = 0;

	std::priority_queue<DummyPath> frontier;

	frontier.push({origin, 0});

	while (!frontier.empty())
	{
		auto P = frontier.top();
		frontier.pop();

		if (P.length > distance[P.last])
			continue;

		if (P.last == destination)
			break;

		for (auto& v : G.neighbors(P.last))
		{
			auto d = P.length + v.weight();
			if (distance[v] > d)
			{
				distance[v] = d;
				frontier.push({v, d});
			}
		}
	}

	return distance;
}

Path Dijkstra(const Graph& G, Graph::Vertex origin, Graph::Vertex destination)
{
	Path P;

	auto distance = DijkstraCost(G, origin, destination);

	Distance remaining = distance[destination];
	// 	std::cout << "distance = " << distance << std::endl;

	if (remaining == INF) // not in the same connected component
		return P;

	P.emplace_back(destination, 0);

	while (P.front() != origin)
	{
		auto l = P.front();
		for (const auto& v : G.inneighbors(l))
		{
			if (remaining == distance[v] + v.weight())
			{
				P.emplace_front(v, v.weight());
				remaining -= v.weight();
				break;
			}
		}
	}

	return P;
}
