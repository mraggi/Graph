#include "ShortestPaths.hpp"

// using Distance = Graph::sumweight_t;
// using Vertex = Vertex;

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
	void reserve(size_t amount) { this->c.reserve(amount); }
};
#include "VectorHelpers.hpp"

DistanceAndParent DijkstraDistance(const Graph& G, Vertex origin, Vertex destination)
{
	DistanceAndParent result(G.num_vertices());

	result.distance[origin] = 0;

	PriorityQueueWithReserve<DummyPath> frontier;
	frontier.reserve(G.num_vertices() - 1);

	frontier.emplace(origin, 0);

	while (!frontier.empty())
	{
		auto P = frontier.top();
		frontier.pop();

		if (P.length > result.distance[P.last])
			continue;

		if (P.last == destination)
			break;

		for (auto& v : G.neighbors(P.last))
		{
			auto d = P.length + v.weight();
			if (result.distance[v] > d)
			{
				result.distance[v] = d;
				result.parent[v] = P.last;
				frontier.emplace(v, d);
			}
		}
	}

	return result;
}

Path Dijkstra(const Graph& G, Vertex origin, Vertex destination)
{
	Path P;

	if (origin == destination)
	{
		P.emplace_back(origin, 0);
		return P;
	}

	auto result = DijkstraDistance(G, origin, destination);
	auto& parent = result.parent;

	auto remaining = result.distance[destination];

	if (remaining == INF)
		return P;

	do
	{
		auto previous = destination;
		destination = parent[destination];
		auto d = result.distance[previous] - result.distance[destination];
		P.emplace_front(previous, d);
	} while (destination != origin);

	P.emplace_front(origin, 0);

	return P;
}
