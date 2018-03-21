#include "ShortestPaths.hpp"

using Distance = Graph::sumweight_t;
using Vertex = Graph::Vertex;

const auto INF = std::numeric_limits<Distance>::max();

struct DummyPath
{
	DummyPath(Vertex v, Distance d) : last(v), length(d) {}
	Vertex last;
	Distance length;
};

inline bool operator<(const DummyPath& a, const DummyPath& b) { return a.length > b.length; }

template <class T>
class PriorityQueueWithReserve : public std::priority_queue<T>
{
public:
	void reserve(size_t amount)
	{
		this->c.reserve(amount);
	}
};

std::vector<Distance> DijkstraCost(const Graph& G, Graph::Vertex origin, Graph::Vertex destination)
{
	std::vector<Distance> distance(G.num_vertices(), INF);
	distance[origin] = 0;

	PriorityQueueWithReserve<DummyPath> frontier;
	frontier.reserve(G.num_vertices()-1);

	frontier.emplace(origin, 0);

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
				frontier.emplace(v, d);
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
